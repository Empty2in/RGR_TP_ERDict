#include "AddOperators.h"
#include "StreamGuard.h"
#include "InputException.h"
#include "Phrases.h"
#include "AddStruct.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <Windows.h>


namespace elina {

    void checkCorretIn(std::istream& in) {
        if (!in) {
            throw WrongWord();
        }
    }
    void openFile(std::fstream& in, std::string& fileName) {
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
    std::string helpInWord(std::istream& in, std::string phrase) {
        std::cout << phrase;
        dictWord word;
        in >> word;
        checkCorretIn(in);
        return word.word_;
    }
    void readManyTransl(std::istream& in, dictSet& list) {
        std::cout << insertRussianWord << whenStop;
        dictWord newTransl;
        while (std::cin) {
            std::cin >> newTransl;
            if (newTransl.word_ == "x" || newTransl.word_ == "÷") {
                break;
            }
            list.insert(newTransl.word_);
        }
    }

    void readDictFromFile(std::fstream& in, DictEngRus& dictionary) {
        dictName name;
        in >> name;
        checkCorretIn(in);
        while (!in.eof()) {
            firstFileWord newWord;
            in >> newWord;
            checkCorretIn(in);
            fileSet buf;
            in >> buf;
            checkCorretIn(in);
            dictionary.insertManyTransl(newWord.word_, buf.list_);
        }
        in.close();
    }

    void creatFileDict(DictEngRus& dictionary) {
        std::fstream in;
        std::string fileName;
        openFile(in, fileName);
        readDictFromFile(in, dictionary);
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

    void mainMenu() {
        char com = ' ';
        while (com) {
            std::cout << mainMenuPhrase;
            std::cin >> com;
            switch (com) {
            case '1': checkEmptyDictionary(); break;
            case '2': checkFileDict(); break;
            case '3': checkTwoDicts(); break;
            case '4': return;
            default: std::cout << defaultPhrase; std::cin.ignore(); break;
            }
        }
    }
    void actWithDict(DictEngRus& dictionary) {
        char com = ' ';
        while (com) {
            std::cout << actWithDictPhrase;
            std::cin >> com;
            switch (com) {
            case '1': checkInsert(dictionary); break;
            case '2': checkDelete(dictionary); break;
            case '3': checkSearch(dictionary); break;
            case '4': checkOneWord(dictionary); break;
            case '5': writeToFile(dictionary); break;
            case '6': return;
            default: std::cout << defaultPhrase; std::cin.ignore(); break;
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

        char com = ' ';
        while (com) {
            std::cout << checkTwoDictsPhrase;
            std::cin >> com;
            switch (com) {
            case '1': checkMerge(dictionary1, dictionary2); break;
            case '2': checkEqual(dictionary1, dictionary2); break;
            case '3': return;
            default: std::cout << defaultPhrase; std::cin.ignore(); break;
            }
        }
    }
    void checkMerge(DictEngRus& dictionary1, DictEngRus& dictionary2) {
        std::cout << "Dictionaries befor merge:\n"
            << dictionary1
            << '\n'
            << dictionary2;
        dictionary1.merge(dictionary2);
        std::cout << "\nDictionaries after merge:\n"
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
        char com = ' ';
        while (com) {
            std::cout << checkInsertPhrase;
            std::cin >> com;
            switch (com) {
            case '1': insertOneWord(dictionary); break;
            case '2': insertManyWords(dictionary); break;
            case '3': insertOneTranslate(dictionary); break;
            case '4': insertManyTranslate(dictionary); break;
            case '5': changeTranslate(dictionary); break;
            case '6': return;
            default: std::cout << defaultPhrase; std::cin.ignore(); break;
            }
        }
    }
    void insertOneWord(DictEngRus& dictionary) {
        std::cout << (
            dictionary.insertWord(helpInWord(std::cin, insertEngWord)) ? 
            "Success insert.\n" : 
            "This word is already in dictionary.\n"
            );
        std::cout << dictionary;
        return;
    }
    void insertManyWords(DictEngRus& dictionary) {
        std::cout << insertEngWord << whenStop;
        dictWord newWord;
        while (std::cin) {
            std::cin >> newWord;
            if (newWord.word_ == "x" || newWord.word_ == "÷") {
                break;
            }
            dictionary.insertWord(newWord.word_);
        }
        std::cout << dictionary;
        return;
    }
    void insertOneTranslate(DictEngRus& dictionary) {
        std::string newWord = helpInWord(std::cin, engWordForTransl);
        std::string newTransl = helpInWord(std::cin, insertRussianWord);
        std::cout << (
            dictionary.insertTranslate(newWord, newTransl) ?
            "Success insert.\n" :
            "This word is already in dictionary.\n"
            );
        std::cout << dictionary;
        return;
    }
    void insertManyTranslate(DictEngRus& dictionary) {
        std::string newWord = helpInWord(std::cin, engWordForTransl);
        dictSet list;
        readManyTransl(std::cin, list);
        std::cout << (
            dictionary.insertManyTransl(newWord, list) ?
            "Success insert.\n" :
            "This word is already in dictionary.\n"
            );
        std::cout << dictionary;
        return;
    }

    void changeTranslate(DictEngRus& dictionary) {
        std::string newWord = helpInWord(std::cin, engWordForTransl);
        dictSet list;
        readManyTransl(std::cin, list);
        std::cout << (
            dictionary.changeAllTransl(newWord, list) ?
            "Success change.\n" :
            "This word isn't in dictionary.\n"
            );
        std::cout << dictionary;
        return;
    }

    void checkDelete(DictEngRus& dictionary) {
        char com = ' ';
        while (com) {
            std::cout << checkDeletePhrase;
            std::cin >> com;
            switch (com) {
            case '1': checkOneWordDelete(dictionary); break;
            case '2': checkOneTranslDelete(dictionary); break;
            case '3': checkAllTranslDelete(dictionary); break;
            case '4': return;
            default: std::cout << defaultPhrase; std::cin.ignore(); break;
            }
        }
    }
    void checkOneWordDelete(DictEngRus& dictionary) {
        std::cout << dictionary;
        std::cout << (
            dictionary.deleteWord(helpInWord(std::cin, deleteEngWord)) ?
            "Success delete.\n" :
            "This word isn't in dictionary.\n"
            );
        std::cout << dictionary;
        return;
    }
    void checkOneTranslDelete(DictEngRus& dictionary) {
        std::cout << dictionary;
        std::string word = helpInWord(std::cin, deleteEngWord);
        std::string delTransl = helpInWord(std::cin, deleteTransl);
        std::cout << (
            dictionary.deleteTranslate(word, delTransl) ?
            "Success delete.\n" :
            "This word isn't in dictionary.\n"
            );
        std::cout << dictionary;
        return;
    }
    void checkAllTranslDelete(DictEngRus& dictionary) {
        std::cout << dictionary;
        std::cout << (
            dictionary.deleteAllTransl(helpInWord(std::cin, deleteWordAllTransl)) ?
            "Success delete.\n" :
            "This word isn't in dictionary.\n"
            );
        std::cout << dictionary;
        return;
    }

    void checkSearch(DictEngRus& dictionary) {
        std::cout << dictionary;
        std::cout << (dictionary.searchWord(helpInWord(std::cin, searchWord)) ?
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

    void checkOneWord(DictEngRus& dictionary) {
        std::cout << dictionary;
        std::string word = helpInWord(std::cin, infoWord);
        std::cout << "\nInfo about word '" << word << "' :";
        std::cout << "\n\tTranslations: " << dictionary.getTranslate(word);
        std::cout << "\n\tCount of translations: " << dictionary.getTranslCount(word);
        std::cout << "\n\tCount of words on dictionary: " << dictionary.getCountOfWord();
        return;
    }
}