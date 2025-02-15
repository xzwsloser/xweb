// @Author: loser
#include "StringUtils.h"
#include <string>
#include <vector>

namespace xweb {

// 1,2,3,4,5,6 -> 1 2 3 4 5 6
void StringUtils::Split(const std::string& origin, const std::string& delimter,
                        std::vector<std::string> &result, bool keep_delimter) 
{
  int end = 0;
  int start = 0;
  while (start < origin.size() &&
         (end = origin.find(delimter, start)) != std::string::npos) {
    if (!keep_delimter) {
      result.push_back(origin.substr(start, end - start));
    } else {
      result.push_back(origin.substr(start, end - start + delimter.size()));
    }

    start = end + delimter.size();
  }

  result.push_back(origin.substr(start));
}

std::string StringUtils::Join(const std::vector<std::string>& target,
        const std::string& delimiter)
{
    std::string result = ""; 
    for(int i = 0 ; i < target.size() ; i ++) {
        result += target[i];
        if(i != (target.size() - 1)) {
            result += delimiter;
        }
    } 
    return result;
}

} // namespace xweb
