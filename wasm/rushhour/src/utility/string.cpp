#include "../common.h"

namespace utility
{
    std::vector<std::string> split(const std::string str, const std::string regex_str)
    {
        std::regex regexz(regex_str);
        std::vector<std::string> list(std::sregex_token_iterator(str.begin(), str.end(), regexz, -1),
                                        std::sregex_token_iterator());
        return list;
    }

    std::string ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        return s;
    }

    // trim from end (in place)
    std::string rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
        return s;
    }

    // trim from both ends (in place)
    std::string trim(std::string &s) {
        ltrim(s);
        rtrim(s);
        return s;
    }
}; // namespace utility