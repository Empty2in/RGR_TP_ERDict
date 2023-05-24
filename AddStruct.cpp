#include "AddStruct.h"
#include "InputException.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <sstream>
#include <string>

namespace elina {

    bool checkWord(std::string word) {
        return std::all_of(
            word.begin(),
            word.end(),
            [](unsigned char c)
            { return (std::isalpha(c) || c == ' ' || c == '-'); }
        );
    }
    std::istream& operator>>(std::istream& in, dictName& word) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        std::getline(in, word.word_);
        if (word.word_ != "DICTIONARY:") {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, dictWord& word) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        if (in.peek() == '\n') {
            in.ignore(1000, '\n');
        }
        std::getline(in, word.word_, '\n');
        if (!checkWord(word.word_)) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, firstFileWord& word) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        std::getline(in, word.word_, ' ');
        if (!checkWord(word.word_)) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, fileWord& word) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        std::getline(in, word.word_, ';');
        if (!checkWord(word.word_)) {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, fileSet& list) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        fileSet temp;
        std::string str;
        std::getline(in, str, '\n');
        std::istringstream iss(str);
        while (!iss.eof()) {
            fileWord w;
            iss >> w;
            if (in && w.word_.size() != 0) {
                temp.list_.insert(w.word_);
            }
        }
        if (in) {
            list = temp;
        }
        return in;
    }
}
    