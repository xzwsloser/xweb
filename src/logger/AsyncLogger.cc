// @Author: loser
#include "AsyncLogger.h"
#include "LogFile.h"
#include <cassert>
#include <functional>

AsyncLogger::AsyncLogger(std::string logFileName_, int flushInterval)
    : flushInterval_(flushInterval), is_running_(false),
      base_name_(logFileName_), currentBuffer_(new Buffer),
      nextBuffer_(new Buffer), latch_(1) {
  assert(logFileName_.size() > 1);
  currentBuffer_->bzero();
  nextBuffer_->bzero();
  buffers_.reserve(16); // buffer queue size
}

void AsyncLogger::start() {
  is_running_ = true;
  thread_ = std::thread{std::bind(&AsyncLogger::threadFunc, this)};
  latch_.wait();
}

void AsyncLogger::stop() {
  is_running_ = false;
  condition_.notify_one();
  thread_.join();
}

AsyncLogger::~AsyncLogger() {
  if (is_running_)
    stop();
}

// the producer thread will use this function to produce log
void AsyncLogger::append(const char *log_line, size_t len) {
  std::lock_guard<std::mutex> lock{mutex_};
  if (currentBuffer_->avaliable() > len) {
    currentBuffer_->append(log_line, len);
  }

  else {
    buffers_.push_back(currentBuffer_); // copy the buffer
    currentBuffer_.reset();
    if (nextBuffer_ != nullptr) {
      currentBuffer_ = std::move(nextBuffer_); // swap the buffer
    } else {
      currentBuffer_.reset(new Buffer);
    }
    currentBuffer_->append(log_line, len);
    condition_.notify_one();
  }
}

// the consumer will call this function to write into file from buffer_
void AsyncLogger::threadFunc() {
  assert(is_running_ == true);
  latch_.countDown();
  LogFile output{base_name_};
  BufferPtr newBuffer1{new Buffer};
  BufferPtr newBuffer2{new Buffer};

  newBuffer1->bzero();
  newBuffer2->bzero();
  BufferVector buffersToWrite;
  buffersToWrite.reserve(16);
  while (is_running_) {
    // one of the new buffer is empty and the buffersToWrite is empty
    assert(newBuffer1 && newBuffer2->length() == 0);
    assert(newBuffer2 && newBuffer1->length() == 0);
    assert(buffersToWrite.empty());

    {
      std::unique_lock<std::mutex> lock{mutex_};
      if (buffers_.empty()) {
        condition_.wait_for(lock, std::chrono::seconds(flushInterval_));
      }
      buffers_.push_back(currentBuffer_);
      currentBuffer_.reset();
      currentBuffer_ = std::move(newBuffer1);
      buffersToWrite.swap(buffers_);
      if (!nextBuffer_) {
        nextBuffer_ = std::move(newBuffer2);
      }
    }
    assert(!buffersToWrite.empty());

    if (buffersToWrite.size() > 25) {
      buffersToWrite.erase(buffersToWrite.begin() + 2, buffersToWrite.end());
    }

    for (const auto &buffer : buffersToWrite) {
      output.append(buffer->data(), buffer->length());
    }

    if (buffersToWrite.size() > 2) {
      buffersToWrite.resize(2);
    }

    if (!newBuffer1) {
      assert(!buffersToWrite.empty());
      newBuffer1 = buffersToWrite.back();
      buffersToWrite.pop_back();
      newBuffer1->reset();
    }

    if (!newBuffer2) {
      assert(!buffersToWrite.empty());
      newBuffer2 = buffersToWrite.back();
      buffersToWrite.pop_back();
      newBuffer2->reset();
    }

    buffersToWrite.clear();
    output.flush();
  }
  output.flush();
}
