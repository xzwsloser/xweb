// @Author: loser
#pragma once
#include <system_error>

namespace xweb {

class nocopyable {
public:
    nocopyable() = default;            
    ~nocopyable() = default;
private:
    nocopyable(const nocopyable&) = delete;
    nocopyable& operator=(const nocopyable&) = delete;
};

}
