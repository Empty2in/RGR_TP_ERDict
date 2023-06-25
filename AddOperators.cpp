#include "AddOperators.h"
#include "StreamGuard.h"
#include "InputException.h"
#include "AddStruct.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <sstream>

namespace elina {

    std::string mainMenuPhrase = "\nEnter the number of which English-Russian Dictionary you need:\n1. Make empty dictionary.\n2. Make dictionary from file.\n3. Exit.\n";
    std::string defaultPhrase = "\nOps, enter command in list, please!\n";
    std::string actWithDictPhrase = "\nEnter your command:\nINSERT <key> <set_transl> - insert word with translate (optional);\nADDTRANSL <key> <set_transl> - add new translation for word in dict;\nCHANGETR <key> - change all translate(old translate will be clear);\nDELETE KEY <key> - delete all translate and key;\nDELETE ONE <key> <word_transl> - delete one translate of word;\nDELETE TRANSL <key> -delete all translate of word;\nSEARCH <key> - check if word in dictionary;\nINFO <key> - print info about key in dictionary;\nMERGE - merge dictionaries;\nEQUAL - compare dictionaries;\nCOUNT - check count of words in dictionary;\nCLEAR - clear current dictionary;\nPRINT - print current dictionary;\nSAVE - save current dictionary;\nHELP - action with dictionary;\nEXIT - close programm;\n\n";

    void openFile(std::fstream& in) {
        std::string fileName;
        std::cout << "Enter name of file: ";
        std::cin >> fileName;
        in.open(fileName);
        auto dot = fileName.find_first_of('.');
        auto fmt = fileName.substr(dot + 1);
        if (!in.is_open() || dot == std::string::npos || fmt != "txt") {
            throw IncorrectFile();
        }
        if (in.peek() == EOF) {
            throw EmptyFile();
        }
    }
    void checkCorretIn(std::istream& in) {
        if (!in) {
            throw WrongWord();
        }
    }
    void writeToFile(DictEngRus& dictionary) {
        std::ofstream out;
        std::string fileName;
        std::cout << "Enter name of file: ";
        std::cin >> fileName;
        out.open(fileName);
        out << dictionary;
        out.close();
    }
    std::string helpInWord(std::istream& in) {
        dictWord word;
        in >> word;
        checkCorretIn(in);
        return word.word_;
    }
    void creatFileDict(DictEngRus& dictionary) {
        std::fstream in;
        openFile(in);
        readDictFromFile(in, dictionary);
        std::cout << dictionary;
    }
    void readDictFromFile(std::fstream& in, DictEngRus& dictionary) {
        dictName name;
        in >> name;
        checkCorretIn(in);
        while (!in.eof()) {
            dictStr str;
            in >> str;
            checkCorretIn(in);
            dictionary.insertWord(str.word_, str.list_);
        }
        in.close();
    }

    void mainMenu() {
        char com = ' ';
        std::cout << mainMenuPhrase;
        std::cin >> com;
        switch (com) {
        case '1': checkEmptyDictionary(); break;
        case '2': checkFileDict(); break;
        case '3': return;
        default: std::cout << "\nChoose number in menu.\n"; break;
        }
    }

    void checkFileDict() {
        DictEngRus dictionary;
        creatFileDict(dictionary);
        actWithDict(dictionary);
    }
    void checkEmptyDictionary() {
        DictEngRus dictionary;
        actWithDict(dictionary);
    }

    void actWithDict(DictEngRus& dictionary) {
        std::string com = " ";
        std::cout << actWithDictPhrase;
        while (com != "EXIT") {
            std::cin >> com;
            if (com == "INSERT") {
                insertWord(dictionary);
            }
            else if (com == "ADDTRANSL") {
                addTransl(dictionary);
            }
            else if (com == "CHANGETR") {
                changeTranslate(dictionary);
            }
            else if (com == "SEARCH") {
                search(dictionary);
            }
            else if (com == "DELETE") {
                deleted(dictionary);
            }
            else if (com == "INFO") {
                info(dictionary);
            }
            else if (com == "MERGE") {
                merge(dictionary);
            }
            else if (com == "EQUAL") {
                equal(dictionary);
            }
            else if (com == "CLEAR") {
                dictionary.clear();
                std::cout << "Succsess cleared";
            }
            else if (com == "PRINT") {
                std::cout << dictionary;
            }
            else if (com == "SAVE") {
                writeToFile(dictionary);
                std::cout << "Sucssess saved\n";
            }
            else if (com == "COUNT") {
                std::cout << "Count of words on dictionary: " << dictionary.getCountOfWord() << "\n";
            }
            else if (com == "HELP") {
                std::cout << actWithDictPhrase;
            }
            else if (com == "EXIT") {
                break;
            }
            else {
                std::cout << defaultPhrase;
            }
        }
    }

    void insertWord(DictEngRus& dictionary) {
        dictStr str;
        std::cin >> str;
        checkCorretIn(std::cin);
        std::cout << (
            dictionary.insertWord(str.word_, str.list_) ?
            "Success insert.\n" :
            "This word is already in dictionary.\n"
            );
    }
    void addTransl(DictEngRus& dictionary) {
        dictStr str;
        std::cin >> str;
        checkCorretIn(std::cin);
        std::cout << (
            dictionary.insertTransl(str.word_, str.list_) ?
            "Success insert.\n" :
            "This word isn't in dictionary.\n"
            );
    }
    void changeTranslate(DictEngRus& dictionary) {
        dictStr str;
        std::cin >> str;
        checkCorretIn(std::cin);
        std::cout << (
            dictionary.changeAllTransl(str.word_, str.list_) ?
            "Success change.\n" :
            "This word isn't in dictionary.\n"
            );
    }

    void deleted(DictEngRus& dictionary) {
        std::string com;
        std::cin >> com;
        if (com == "KEY") {
            oneWordDelete(dictionary);
        }
        else if (com == "TRANSL") {
            allTranslDelete(dictionary);
        }
        else if (com == "ONE") {
            oneTranslDelete(dictionary);
        }
        else {
            std::cout << defaultPhrase;
        }
    }
    void oneWordDelete(DictEngRus& dictionary) {
        std::cout << (
            dictionary.deleteWord(helpInWord(std::cin)) ?
            "Success delete.\n" :
            "This word isn't in dictionary.\n"
            );
    }
    void oneTranslDelete(DictEngRus& dictionary) {
        std::string word = helpInWord(std::cin);
        std::string delTransl = helpInWord(std::cin);
        std::cout << (
            dictionary.deleteTranslate(word, delTransl) ?
            "Success delete.\n" :
            "This word isn't in dictionary.\n"
            );
    }
    void allTranslDelete(DictEngRus& dictionary) {
        std::cout << (
            dictionary.deleteAllTransl(helpInWord(std::cin)) ?
            "Success delete.\n" :
            "This word isn't in dictionary.\n"
            );
    }

    void search(const DictEngRus& dictionary) {
        std::cout << (dictionary.searchWord(helpInWord(std::cin)) ?
            "This word is in dictionary\n" :
            "This word isn't in dictionary\n");
    }
    void info(const DictEngRus& dictionary) {
        std::string word = helpInWord(std::cin);
        if (dictionary.searchWord(word)) {
            std::cout << "\nInfo about word '" << word << "' :";
            std::cout << "\n\tTranslations: " << dictionary.getTranslate(word);
            std::cout << "\n\tCount of translations: " << dictionary.getTranslCount(word);
            std::cout << "\n";
        }
        else {
            std::cout << "Word isn't in dictionary.\n";
        }
    }

    void merge(DictEngRus& dictionary) {
        DictEngRus addDictionary;
        creatFileDict(addDictionary);
        std::cout << (
            (dictionary.merge(addDictionary)) ?
            "Sucsess merged\n" :
            "Can't merge (the dicts may be equal)\n"
        );
    }
    void equal(const DictEngRus& dictionary) {
        DictEngRus addDictionary;
        creatFileDict(addDictionary);
        std::cout << (
            dictionary.isEqual(addDictionary) ?
            "Dictionaries are equal\n" :
            "Dictionaries aren't equal\n"
            );
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
        out << std::setw(20) << std::left << par.first << par.second << '\n';
        return out;
    }
    std::ostream& operator <<(std::ostream& out, const DictEngRus& tree) {
        std::ostream::sentry sentry(out);
        if (!sentry) {
            return out;
        }
        StreamGuard stream(out);
        out << "DICTIONARY:\n";
        std::for_each(
            tree.cbegin(),
            tree.cend(),
            [&out](const dictPair& it)
            { out << it; }
        );
        return out;
    }
}