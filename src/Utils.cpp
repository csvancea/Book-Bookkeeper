#include <Utils.h>
#include <algorithm>

namespace Utils
{
    std::vector<std::string> Split(const std::string& str, const std::string& delim)
    {
        size_t pos_start = 0, pos_end, delim_len = delim.length();
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = str.find(delim, pos_start)) != std::string::npos) {
            token = str.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(str.substr(pos_start));
        return res;
    }

    std::string Trim(const std::string& str, const std::string& whitespace)
    {
        const auto strBegin = str.find_first_not_of(whitespace);
        if (strBegin == std::string::npos)
            return ""; // no content

        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }

    std::string ToLower(const std::string& str)
    {
        std::string ret;
        
        std::transform(str.begin(), str.end(), std::back_inserter(ret), ::tolower);
        return ret;
    }
}
