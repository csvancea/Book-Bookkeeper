#include <Utils.h>

namespace Utils
{
    std::vector<std::string> Split(std::string str, std::string delim)
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
}
