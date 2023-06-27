#include <iostream>
#include <algorithm>
#include <functional>
#include <string>

#include "AddStruct.h"
#include "InputException.h"
#include "StreamGuard.h"

namespace elina {

    bool checkWord(const std::string& word) {
        auto ans = std::all_of(
            word.begin(),
            word.end(),
            [](unsigned char c)
            { return (std::isalpha(c) || c == ' ' || c == '-'); }
        );
        return ans;
    }
    std::istream& operator>>(std::istream& in, dictName& name) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        dictName temp;
        std::getline(in, temp.dictName_);
        if (temp.dictName_ != "DICTIONARY:") {
            in.setstate(std::ios::failbit);
        }
        else {
            name = temp;
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, dictWord& word) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        dictWord temp;
        in >> temp.word_;
        if (!checkWord(temp.word_) || temp.word_ == "") {
            in.setstate(std::ios::failbit);
        }
        else {
            word = temp;
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, trans& word) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        trans temp;
        char character = in.get();
        while (character != '\n' && character != ';') {
            temp.word_.push_back(character);
            character = in.get();
        }
        if (!checkWord(temp.word_) || character == '\n') {
            in.setstate(std::ios::failbit);
        }
        else {
            word = temp;
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, translist& list) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        translist temp;
        char newLine = '\0';
        while (!in.eof() && (newLine != '\n')) {
            trans trans;
            in >> trans;
            if (in) {
                temp.list_.insert(trans.word_);
            }
            else {
                break;
            }
            newLine = in.peek();
        }
        if (in) {
            list = temp;
        }
        return in;
    }
    std::istream& operator>>(std::istream& in, dictStr& str) {
        std::istream::sentry sentry(in);
        if (!sentry) {
            return in;
        }
        dictWord word;
        translist list;
        in >> word;
        if (!in.eof() && in.peek() != '\n') {
            in >> list;
        }
        if (!in.fail()) {
            str.word_ = word.word_;
            str.list_ = list.list_;
        }
        return in;
    }
    