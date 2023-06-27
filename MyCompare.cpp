#include <algorithm>
#include <functional>

#include "MyCompare.h"

namespace elina {
    using namespace std::placeholders;

    void toLowerStr(std::string& word) {
        std::transform(
            word.begin(),
            word.end(),
            word.begin(),
            [](char c)
            { return std::tolower(c); }
        );
    }

    bool dictComp::operator() (std::string word1, std::string word2) const {
        toLowerStr(word1);
        toLowerStr(word2);
        return word1 < word2;
    }
}