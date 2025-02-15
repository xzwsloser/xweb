// @Author: loser
#include "IOUtils.h"
#include <cerrno>
#define MAX_BUFF 4096

namespace xweb {

ssize_t IOUtils::readn(int fd, void *buff, size_t n) {
  size_t nleft = n;
  ssize_t readSum = 0;
  ssize_t nread = 0;
  char *ptr = (char *)buff;
  while (nleft > 0) {
    if ((nread = read(fd, ptr, n)) < 0) {
      // interupt by signal
      if (errno == EINTR) {
        continue;
      } else if (errno == EAGAIN) {
        // task dont't be finished
        return readSum;
      } else {
        return -1;
      }
    } else if (nread == 0) {
      break;
    }

    readSum += nread;
    nleft -= nread;
    ptr += nread;
  }
  return readSum;
}

ssize_t IOUtils::readn(int fd, std::string &inBuffer, bool &zero) {
  ssize_t nread = 0;
  ssize_t readSum = 0;
  while (true) {
    char buffer[MAX_BUFF];
    if ((nread = read(fd, buffer, sizeof(buffer))) < 0) {
      if (errno == EINTR) {
        continue;
      } else if (errno == EAGAIN) {
        return readSum;
      } else {
        return -1;
      }
    } else if (nread == 0) {
      zero = true;
      break;
    }
    readSum += nread;
    inBuffer += std::string(buffer, buffer + nread);
  }
  return readSum;
}

ssize_t readn(int fd, std::string &inBuffer) {
  ssize_t nread = 0;
  ssize_t readSum = 0;
  while (true) {
    char buffer[MAX_BUFF];
    if ((nread = read(fd, buffer, sizeof(buffer))) < 0) {
      if (errno == EINTR) {
        continue;
      } else if (errno == EAGAIN) {
        return readSum;
      } else {
        return -1;
      }
    } else if (nread == 0) {
      break;
    }
    readSum += nread;
    inBuffer += std::string(buffer, buffer + nread);
  }
  return readSum;
}

ssize_t IOUtils::writen(int fd, void *buff, size_t n) {
  size_t nleft = n;
  ssize_t writeSum = 0;
  ssize_t nwrite = 0;
  char *ptr = (char *)buff;
  while (nleft > 0) {
    if ((nwrite = write(fd, ptr, n)) < 0) {
      if (errno == EINTR) {
        nwrite = 0;
        continue;
      } else if (errno == EAGAIN) {
        break;
      } else {
        return -1;
      }
    }
    nleft -= nwrite;
    writeSum += nwrite;
    ptr += nwrite;
  }
  return writeSum;
}

ssize_t IOUtils::writen(int fd, std::string &sbuff) {
  size_t nleft = sbuff.size();
  ssize_t writeSum = 0;
  ssize_t nwrite = 0;
  const char *ptr = sbuff.c_str();
  while (nleft > 0) {
    if ((nwrite = write(fd, ptr, nleft)) < 0) {
      if (errno == EINTR) {
        nwrite = 0;
        continue;
      } else if (errno == EAGAIN) {
        break;
      } else {
        return -1;
      }
    }
    writeSum += nwrite;
    nleft -= nwrite;
    ptr += nwrite;
  }

  if (writeSum == static_cast<int>(sbuff.size())) {
    sbuff.clear();
  } else {
    sbuff = sbuff.substr(writeSum);
  }
  return writeSum;
}

}
