// @Author: loser
#include "HttpStatusCode.h"

namespace xweb {

std::string HttpStatusCode::CoverToStr(StatusCode code) 
{
  switch (code) {
  case StatusCode::OK:
    return "OK";
  case StatusCode::CREATED:
    return "Created";
  case StatusCode::ACCEPTED:
    return "Accepted";
  case StatusCode::NO_CONTENT:
    return "No Content";
  case StatusCode::PARTIAL_CONTENT:
    return "Partial Content";
  case StatusCode::BAD_REQUEST:
    return "Bad Request";
  case StatusCode::UNAUTHORIZED:
    return "Unauthorized";
  case StatusCode::FORBIDDEN:
    return "Forbidden";
  case StatusCode::NOT_FOUND:
    return "Not Found";
  case StatusCode::METHOD_NOT_ALLOWED:
    return "Method Not Allowed";
  case StatusCode::INTERNAL_SERVER_ERROR:
    return "Internal Server Error";
  case StatusCode::MOVED_PERMANENTLY:
    return "Moved Permanently";
  case StatusCode::FOUND:
    return "Found";
  default:
    return "Unknown";
  }
}

StatusCode HttpStatusCode::CoverToCode(const std::string& code)
{
  if (code == "OK") {
    return StatusCode::OK;
  } else if (code == "Created") {
    return StatusCode::CREATED;
  } else if (code == "Accepted") {
    return StatusCode::ACCEPTED;
  } else if (code == "No Content") {
    return StatusCode::NO_CONTENT;
  } else if (code == "Partial Content") {
    return StatusCode::PARTIAL_CONTENT;
  } else if (code == "Bad Request") {
    return StatusCode::BAD_REQUEST;
  } else if (code == "Unauthorized") {
    return StatusCode::UNAUTHORIZED;
  } else if (code == "Forbidden") {
    return StatusCode::FORBIDDEN;
  } else if (code == "Not Found") {
    return StatusCode::NOT_FOUND;
  } else if (code == "Method Not Allowed") {
    return StatusCode::METHOD_NOT_ALLOWED;
  } else if (code == "Internal Server Error") {
    return StatusCode::INTERNAL_SERVER_ERROR;
  } else if (code == "Moved Permanently") {
    return StatusCode::MOVED_PERMANENTLY;
  } else if (code == "Found") {
    return StatusCode::FOUND;
  } else {
    return StatusCode::UNKNOWN;
  }
}

StatusCode HttpStatusCode::CoverToCode(int code)
{
    switch (code) {
    case 200:
        return StatusCode::OK;
    case 201:
        return StatusCode::CREATED;
    case 202:
        return StatusCode::ACCEPTED;
    case 204:
        return StatusCode::NO_CONTENT;
    case 206:
        return StatusCode::PARTIAL_CONTENT;
    case 301:
        return StatusCode::MOVED_PERMANENTLY;
    case 302:
        return StatusCode::FOUND;
    case 400:
        return StatusCode::BAD_REQUEST;
    case 401:
        return StatusCode::UNAUTHORIZED;
    case 403:
        return StatusCode::FORBIDDEN;
    case 404:
        return StatusCode::NOT_FOUND;
    case 405:
        return StatusCode::METHOD_NOT_ALLOWED;
    case 500:
        return StatusCode::INTERNAL_SERVER_ERROR;
    default:
        return StatusCode::UNKNOWN;
    }
}

void HttpStatusCode::SetCode(StatusCode code)
{
    code_ = code;
}

StatusCode HttpStatusCode::GetCode()
{
    return code_;
}

}
