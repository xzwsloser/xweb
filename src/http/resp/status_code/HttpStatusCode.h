// @Author: loser
#pragma once
#include <string>

namespace xweb {

enum class StatusCode : int{
  OK = 200,
  CREATED = 201,
  ACCEPTED = 202,
  NO_CONTENT = 204,
  PARTIAL_CONTENT = 206,

  MOVED_PERMANENTLY = 301,
  FOUND = 302,

  BAD_REQUEST = 400,
  UNAUTHORIZED = 401,
  FORBIDDEN = 403,
  NOT_FOUND = 404,
  METHOD_NOT_ALLOWED = 405,

  INTERNAL_SERVER_ERROR = 500,

  UNKNOWN = -1
};

class HttpStatusCode {
public:
    HttpStatusCode() = default;
    ~HttpStatusCode() = default;
    
    static std::string CoverToStr(StatusCode code);
    static StatusCode CoverToCode(const std::string& str);
    static StatusCode CoverToCode(int code);

    void SetCode(StatusCode code);
    StatusCode GetCode();

    std::string ToString() { return CoverToStr(code_); };

private:
    StatusCode code_;
};

}
