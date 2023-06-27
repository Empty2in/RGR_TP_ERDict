#include <iostream>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <map>

#include "AddOperators.h"
#include "StreamGuard.h"
#include "InputException.h"
#include "AddStruct.h"

namespace elina {

    const std::string MAIN_MENU_PHRASE = "\nEnter the number of which English-Russian Dictionary you need:\n1. Make empty dictionary.\n2. Make dictionary from file.\n3. Exit.\n";
    const std::string defaultPhrase = "\nOps, enter command in list, please!\n";
    const std::string ACT_WITH_DICT_PHRASE = "\nEnter your command:\nINSERT <key> <set_transl> - insert word with translate (optional);\nADDTRANSL <key> <set_transl> - add new translation for word in dict;\nCHANGETR <key> - change all translate(old translate will be clear);\nDELETE KEY <key> - delete all translate and key;\nDELETE ONE <key> <word_transl> - delete one translate of word;\nDELETE TRANSL <key> -delete all translate of word;\nSEARCH <key> - check if word in dictionary;\nINFO <key> - print info about key in dictionary;\nMERGE - merge dictionaries;\nEQUAL - compare dictionaries;\nCOUNT - check count of words in dictionary;\nCLEAR - clear current dictionary;\nPRINT - print current dictionary;\nSAVE - save current dictionary;\nHELP - action with dictionary;\nEXIT - close programm;\n\n";

    bool openFile(std::fstream& in, bool addDict) {
        std::string fileName;
        std::cout << "Enter name of file: ";
        std::cin >> fileName;
        in.open(fileName);
        auto dot = fileName.find_first_of('.');
        auto fmt = fileName.substr(dot + 1);
        if ((!in.is_open() || dot == std::string::npos || fmt != "txt")) {
            if (addDict) {
                std::cout << "Wrong name of file!\n";
                in.close();
                return false;
            }
            else {
                in.close();
                throw IncorrectFile();
            }
        }
    }
    void checkCorretIn(std::istream& in) {
        std::cout << "Wrong input.\nPlease enter in form:\n<command> <key> <transl>; <transl>; .. <transl>;\n";
        in.clear();
        in.ignore();
    }
    bool writeToFile(const DictEngRus& dictionary) {
        std::fstream out;
        if (openFile(out, true)) {
            out << dictionary;
            out.close();
            return true;
        }
        else {
            return false;
        }
    }
    bool creatFileDict(DictEngRus& dictionary, bool addDict) {
        std::fstream in;
        if (openFile(in, addDict)) {
            readDictFromFile(in, dictionary);
            std::cout << dictionary;
            return true;
        }
        else {
            return false;
        }
        
    }
    void readDictFromFile(std::fstream& in, DictEngRus& dictionary) {
        dictName name;
        in >> name;
        if (!in) {
            throw WrongDictName();
        }
        while (!in.eof()) {
            dictStr str;
            in >> str;
            if (!in.fail()) {
                dictionary.insertWord(str.word_, str.list_);
            }
            else if (!in.eof()) {
                in.clear();
            }
        }
        in.close();
    }

    void mainMenu() {
        char com = ' ';
        std::cout << MAIN_MENU_PHRASE;
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
        creatFileDict(dictionary, false);
        actWithDict(dictionary);
    }
    void checkEmptyDictionary() {
        DictEngRus dictionary;
        actWithDict(dictionary);
    }

    void actWithDict(DictEngRus& dictionary) {
        std::cout << ACT_WITH_DICT_PHRASE;
        std::string com = "";
        using functionPair = std::pair< void(*)(DictEngRus&), void(*)(const DictEngRus&) >;
        std::map< std::string, functionPair > menu;
        menu.insert({ "INSERT", { insertWord, nullptr } });
        menu.insert({ "ADDTRANSL", { addTransl, nullptr } });
        menu.insert({ "CHANGETR", { changeTranslate, nullptr } });
        menu.insert({ "SEARCH", { nullptr, search } });
        menu.insert({ "DELETE", { deleted, nullptr } });
        menu.insert({ "INFO", { nullptr, info } });
        menu.insert({ "MERGE", { merge, nullptr } });
        menu.insert({ "EQUAL", { nullptr, equal } });
        menu.insert({ "CLEAR", { clear, nullptr } });
        menu.insert({ "PRINT", { nullptr, print } });
        menu.insert({ "SAVE", { nullptr, save } });
        menu.insert({ "COUNT", { nullptr, count } });

        while (com != "EXIT") {
            std::cin >> com;
            auto menuCom = menu.find(com);
            if (menuCom != menu.cend()) {
                if ((menuCom->second).first) {
                    (menuCom->second).first(dictionary);
                }
                else {
                    (menuCom->second).second(dictionary);
                }
            }
            else if (com == "HELP") {
                std::cout << ACT_WITH_DICT_PHRASE;
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
        if (!std::cin) {
            checkCorretIn(std::cin);
        }
        else {
            std::cout << (
            dictionary.insertWord(str.word_, str.list_) ?
            "Success insert.\n" :
            "This word is already in dictionary.\n"
            );
        }
    }
    void addTransl(DictEngRus& dictionary) {
        dictStr str;
        std::cin >> str;
        if (!std::cin) {
            checkCorretIn(std::cin);
        }
        else {
            std::cout << (
            dictionary.insertTransl(str.word_, str.list_) ?
            "Success insert.\n" :
            "This word isn't in dictionary or transList is empty.\n"
            );
        }
    }
    void changeTranslate(DictEngRus& dictionary) {
        dictStr str;
        std::cin >> str;
        if (!std::cin) {
            checkCorretIn(std::cin);
        }
        else {
            std::cout << (
            dictionary.changeAllTransl(str.word_, str.list_) ?
            "Success change.\n" :
            "Mayde, this word isn't in dictionary or transList.\n"
            );
        }
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
        dictWord word;
        std::cin >> word;
        if (!std::cin) {
            checkCorretIn(std::cin);
        }
        else {
            std::cout << (
            dictionary.deleteWord(word.word_) ?
            "Success delete.\n" :
            "This word isn't in dictionary.\n"
            );
        }
    }
    void oneTranslDelete(DictEngRus& dictionary) {
        dictStr str;
        std::cin >> str;
        if (!std::cin || !str.list_.size() == 1) {
            checkCorretIn(std::cin);
        }
        else {
            std::cout << (
             dictionary.deleteTranslate(str.word_, *(str.list_.begin())) ?
            "Success delete.\n" :
            "This word isn't in dictionary.\n"
            );
        }
    }
    void allTranslDelete(DictEngRus& dictionary) {
        dictWord word;
        std::cin >> word;
        if (!std::cin) {
            checkCorretIn(std::cin);
        }
        else {
            std::cout << (
            dictionary.deleteAllTransl(word.word_) ?
            "Success delete.\n" :
            "This word isn't in dictionary.\n"
            );
        }
    }

    void search(const DictEngRus& dictionary) {
        dictWord word;
        std::cin >> word;
        if (!std::cin) {
            checkCorretIn(std::cin);
        }
        else {
            std::cout << (dictionary.searchWord(word.word_) ?
            "This word is in dictionary\n" :
            "This word isn't in dictionary\n");
        }
    }
    void info(const DictEngRus& dictionary) {
        dictWord word;
        std::cin >> word;
        if (!std::cin) {
            checkCorretIn(std::cin);
        }
        else {
            if (dictionary.searchWord(word.word_)) {
                std::cout << "\nInfo about word '" << word.word_ << "' :";
                std::cout << "\n\tTranslations: " << dictionary.getTranslate(word.word_);
                std::cout << "\n\tCount of translations: " << dictionary.getTranslCount(word.word_);
                std::cout << "\n";
            }
            else {
                std::cout << "Word isn't in dictionary.\n";
            }
        }
    }

    void merge(DictEngRus& dictionary) {
        DictEngRus addDictionary;
        if (creatFileDict(addDictionary, true)) {
            std::cout << (
                (dictionary.merge(addDictionary)) ?
                "Sucsess merged\n" :
                "Can't merge (the dicts may be equal)\n"
                );
        }
    }
    void equal(const DictEngRus& dictionary) {
        DictEngRus addDictionary;
        if (creatFileDict(addDictionary, true)) {
            std::cout << (
                dictionary.isEqual(addDictionary) ?
                "Dictionaries are equal\n" :
                "Dictionaries aren't equal\n"
                );
        }
    }

    void clear(DictEngRus& dictionary) {
        dictionary.clear();
        std::cout << (
            dictionary.isEmpty() ? 
            "Succsess cleared\n" :
            "Can't clear\n" 
            );
    }

    void print(const DictEngRus& dictionary) {
        std::cout << dictionary;
    }

    void save(const DictEngRus& dictionary) {
        std::cout << (
            writeToFile(dictionary) ?
            "Sucssess saved\n" :
            "Problem with save :(\n"
            );
    }

    void count(const DictEngRus& dictionary) {
        std::cout << 
            "Count of words on dictionary: " << 
            dictionary.getCountOfWord() << 
            "\n";
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