#include "AddOperators.h"
#include "StreamGuard.h"

#include "InputException.h"
#include "Phrases.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <Windows.h>

namespace elina {

    void openFile(std::fstream& in, std::string& fileName) {
        std::cout << "Enter name of file: ";
        std::cin >> fileName;
        in.open(fileName);
        if (!in.is_open()) {
            throw IncorrectFile();
        }
        if (in.peek() == EOF) {
            throw EmptyFile();
        }
    }

    void readDictFromFail(std::fstream& in, DictEngRus& dictionary) {
        while (!in.eof()) {
            std::string newWord, newTransl;
            int countTransl = 0;
            std::getline(in, newWord);
            if (!checkWord(newWord)) {
                throw WrongWord();
            }
            in >> countTransl;
            if (in.peek() == ',' || in.peek() == '.') {
                throw WrongInt();
            }
            in.ignore(1000, '\n');
            for (int i = 0; i < countTransl; ++i) {
                std::getline(in, newTransl);
                if (!checkWord(newTransl)) {
                    throw WrongWord();
                }
                dictionary.insertTranslate(newWord, newTransl);
            }
            in.ignore(1000, '\n');
        }
        in.close();
    }

    void creatFileDict(DictEngRus& dictionary) {
        std::fstream in;
        std::string fileName;
        openFile(in, fileName);
        readDictFromFail(in, dictionary);
    }

    bool checkWord(std::string word) {
        for (unsigned char c : word) {
            if (!std::isalpha(c) && c != ' ' && c != '-') {
                return false;
            }
        }
        return true;
    }


    std::string enterWord(std::istream& in) {
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);
        std::string word;
        std::getline(in, word);
        if (word == "x" || word == "÷") {
            return word;
        }
        if (!checkWord(word)) {
            throw WrongWord();
        }
        return word;

    }

    void mainMenu() {
        int com = 1;
        while (com) {
            std::cout << mainMenuPhrase;
            std::cin >> com;
            switch (com) {
            case 1: checkEmptyDictionary(); continue;
            case 2: checkFileDict(); continue;
            case 3: checkTwoDicts(); continue;
            case 4: exit(0);
            default: std::cout << defaultPhrase; continue;
            }
        }
    }

    void actWithDict(DictEngRus& dictionary) {
        int com = 1;
        while (com) {
            std::cout << actWithDictPhrase;
            std::cin >> com;
            switch (com) {
            case 1: checkInsert(dictionary); continue;
            case 2: checkDelete(dictionary); continue;
            case 3: checkSearch(dictionary); continue;
            case 4: checkOneWord(dictionary); continue;
            case 5: return;
            default: std::cout << defaultPhrase; continue;
            }
        }
    }

    void checkEmptyDictionary() {
        DictEngRus dictionary;
        std::cout << dictionary;
        actWithDict(dictionary);
    }
    void checkFileDict() {
        DictEngRus dictionary;
        creatFileDict(dictionary);
        std::cout << dictionary;
        actWithDict(dictionary);
    }

    void checkTwoDicts() {

        DictEngRus dictionary1;
        creatFileDict(dictionary1);
        std::cout << dictionary1;

        DictEngRus dictionary2;
        creatFileDict(dictionary2);
        std::cout << dictionary2;

        int com = 0;
        while (com != 3) {
            std::cout << checkTwoDictsPhrase;
            std::cin >> com;
            switch (com) {
            case 1: checkMerge(dictionary1, dictionary2); continue;
            case 2: checkEqual(dictionary1, dictionary2); continue;
            case 3: return;
            default: std::cout << defaultPhrase; continue;
            }
        }
    }

    void checkMerge(DictEngRus& dictionary1, DictEngRus& dictionary2) {
        std::cout << "Dictionaries befor merge:\n"
            << dictionary1
            << '\n'
            << dictionary2;
        dictionary1.merge(dictionary2);
        std::cout << "Dictionaries after merge:\n"
            << dictionary1
            << '\n'
            << dictionary2;
        return;
    }


    void checkEqual(const DictEngRus& dictionary1, const DictEngRus& dictionary2) {
        std::cout << (
            dictionary1.isEqual(dictionary2) ?
            "Dictionaries are equal\n" :
            "Dictionaries aren't equal\n"
            );
        return;
    }

    void checkInsert(DictEngRus& dictionary) {
        int com = 1;
        while (com) {
            std::cout << checkInsertPhrase;
            std::cin >> com;
            switch (com) {
            case 1: insertOneWord(dictionary); continue;
            case 2: insertManyWords(dictionary); continue;
            case 3: insertOneTranslate(dictionary); continue;
            case 4: insertManyTranslate(dictionary); continue;
            case 5: changeTranslate(dictionary); continue;
            case 6: return;
            default: std::cout << defaultPhrase; continue;
            }
        }
    }
    void insertOneWord(DictEngRus& dictionary) {
        std::cout << insertEngWord;
        std::cin.ignore(1000, '\n');
        dictionary.insertWord(enterWord(std::cin));
        std::cout << dictionary;
        return;
    }
    void insertManyWords(DictEngRus& dictionary) {
        std::cout << insertEngWord << whenStop;
        std::string newWord;
        while (std::cin) {
            newWord = enterWord(std::cin);
            if (newWord == "x" || newWord == "÷") {
                break;
            }
            dictionary.insertWord(newWord);
        }
        std::cout << dictionary;
        return;
    }
    void insertOneTranslate(DictEngRus& dictionary) {
        std::cout << engWordForTransl;
        std::cin.ignore(1000, '\n');
        std::string newWord = enterWord(std::cin);
        std::cout << insertRussianword;
        std::string newTransl = enterWord(std::cin);
        dictionary.insertTranslate(newWord, newTransl);
        std::cout << dictionary;
        return;
    }
    void insertManyTranslate(DictEngRus& dictionary) {
        std::cout << engWordForTransl;
        std::cin.ignore(1000, '\n');
        std::string newWord = enterWord(std::cin);
        dictSet list;
        readManyTransl(std::cin, dictionary);
        dictionary.insertManyTransl(newWord, list);
        std::cout << dictionary;
        return;
    }

    void changeTranslate(DictEngRus& dictionary) {
        std::cout << engWordForTransl;
        std::cin.ignore(1000, '\n');
        std::string newWord = enterWord(std::cin);
        dictSet list;
        readManyTransl(std::cin, dictionary);
        dictionary.changeAllTransl(newWord, list);
    }

    void readManyTransl(std::istream& in, dictSet& list) {
        std::cout << insertRussianword << whenStop;
        std::string newTransl;
        while (std::cin) {
            newTransl = enterWord(std::cin);
            if (newTransl == "x" || newTransl == "÷") {
                break;
            }
            list.insert(newTransl);
        }
    }

    void checkDelete(DictEngRus& dictionary) {
        int com = 1;
        while (com) {
            std::cout << checkDeletePhrase;
            std::cin >> com;
            switch (com) {
            case 1: checkOneWordDelete(dictionary); continue;
            case 2: checkOneTranslDelete(dictionary); continue;
            case 3: checkAllTranslDelete(dictionary); continue;
            case 4: return;
            default: std::cout << defaultPhrase; continue;
            }
        }
    }
    void checkOneWordDelete(DictEngRus& dictionary) {
        std::cout << dictionary;
        std::cout << deleteEngWord;
        std::cin.ignore(1000, '\n');
        dictionary.deleteWord(enterWord(std::cin));
        std::cout << dictionary;
        return;
    }
    void checkOneTranslDelete(DictEngRus& dictionary) {
        std::cout << dictionary;
        std::cout << deleteEngWord;
        std::cin.ignore(1000, '\n');
        std::string word = enterWord(std::cin);
        std::cout << deleteTransl;
        std::string delTransl = enterWord(std::cin);
        dictionary.deleteTranslate(word, delTransl);
        std::cout << dictionary;
        return;
    }
    void checkAllTranslDelete(DictEngRus& dictionary) {
        std::cout << dictionary;
        std::cout << deleteWordAllTransl;
        std::cin.ignore(1000, '\n');
        dictionary.deleteAllTransl(enterWord(std::cin));
        std::cout << dictionary;
        return;
    }

    void checkSearch(DictEngRus& dictionary) {
        std::cout << dictionary;
        std::cout << searchWord;
        std::cin.ignore(1000, '\n');
        std::string word = enterWord(std::cin);
        std::cout << (dictionary.searchWord(word) ?
            "\n\tThis word is in dictionary\n" :
            "\n\tThis word isn't in dictionary\n");
        return;
    }

    std::ostream& operator <<(std::ostream& out, const dictSet& st) {
        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }
        StreamGuard stream(out);
        std::copy(
            st.begin(),
            st.end(),
            std::ostream_iterator< std::string >(out, "; ")
        );
        return out;
    }

    std::ostream& operator <<(std::ostream& out, const dictPair& par) {
        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }
        StreamGuard stream(out);
        out << '\t' << std::setw(20) << std::left << par.first << par.second << '\n';
        return out;
    }

    void checkOneWord(DictEngRus& dictionary) {
        std::cout << dictionary;
        std::cout << infoWord;
        std::cin.ignore(1000, '\n');
        std::string word = enterWord(std::cin);
        std::cout << "\nInfo about word '" << word << "' :";
        std::cout << "\n\tTranslations: " << dictionary.getTranslate(word);
        std::cout << "\n\tCount of translations: " << dictionary.getTranslCount(word);
        std::cout << "\n\tCount of words on dictionary: " << dictionary.getCountOfWord();
        return;
    }
}
