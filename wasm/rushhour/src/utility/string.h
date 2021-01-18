#ifndef STRING_H
#define STRING_H

#include "../common.h"

namespace utility
{
    std::vector<std::string> split(const std::string str, const std::string regex_str);

    std::string ltrim(std::string &s);

    // trim from end (in place)
    std::string rtrim(std::string &s);

    // trim from both ends (in place)
    std::string trim(std::string &s);
}; // namespace utility


#endif