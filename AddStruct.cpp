#include "AddStruct.h"
#include <iostream>
#include <algorithm>
#include <functional>

namespace elina {
    using namespace std::placeholders;

    std::string toLowerStr(std::string& word) {
        std::transform(
            word.begin(),
            word.end(),
            word.begin(),
            [](char c)
            { return std::tolower(c); }
        );
        return word;
    }

    bool dictComp::operator() (std::string word1, std::string word2) const {
        auto ans = std::bind(
            std::less<std::string>(),
            std::bind(toLowerStr, _1),
            std::bind(toLowerStr, _2)
        );
        return static_cast<bool>(ans(word1, word2));
    }


    /* std::istream& operator>>(std::istream& in, dictWord& word) {
         std::istream::sentry sentry(in);
         if (!sentry) {
             return in;
         }
         if (in.peek() == '\n') {
             in.ignore(1000, '\n');
         }
         std::getline(in, word.word_);
         if (!checkWord(word.word_)) {
             in.setstate(std::ios::failbit);
         }
         return in;
     }*/
}
    