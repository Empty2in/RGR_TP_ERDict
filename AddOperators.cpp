#include "AddOperators.h"
#include "StreamGuard.h"
#include "InputException.h"
#include "Phrases.h"

#include <iostream>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <Windows.h>

namespace elina {

    size_t const menuCom = 1;

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

    std::string helpInWord(std::istream& in, std::string phrase, bool ignore) {
        std::cout << phrase;
        /*dictWord word;
        std::cin >> word;*/
        std::string word;
        enterWord(in, word);
        return word;
    }


    bool checkWord(std::string word) {
        return std::all_of(
            word.begin(),
            word.end(),
            [](unsigned char c)
            { return (std::isalpha(c) || c == ' ' || c == '-'); }
        );
    }


    void enterWord(std::istream& in, std::string& word) {
        if (in.peek() == '\n') {
            in.ignore(1000, '\n');
        }
        std::getline(in, word);
        if (!checkWord(word)) {
            throw WrongWord();
        }
    }

    void helpInSize(std::istream& in, size_t& size) {
        in >> size;
        if (in.peek() != '\n' || size == 0) {
            throw WrongInt();
        }
    }


    void readManyTransl(std::istream& in, dictSet& list) {
        std::cout << insertRussianWord << whenStop;
        std::string newTransl;
        while (std::cin) {
            enterWord(std::cin, newTransl);
            if (newTransl == "x" || newTransl == "÷") {
                break;
            }
            list.insert(newTransl);
        }
    }

    void readDictFromFail(std::fstream& in, DictEngRus& dictionary) {
        while (!in.eof()) {
            std::string newWord;
            enterWord(in, newWord);

            size_t countTransl = 0;
            helpInSize(in, countTransl);
            in.ignore(1000, '\n');

            dictSet list;
            for (size_t i = 0; i < countTransl; ++i) {
                std::string newTransl;
                enterWord(in, newTransl);
                list.insert(newTransl);
            }
            dictionary.insertManyTransl(newWord, list);
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
        size_t com = menuCom;
        while (com) {
            std::cout << mainMenuPhrase;
            helpInSize(std::cin, com);
            switch (com) {
            case 1: checkEmptyDictionary(); break;
            case 2: checkFileDict(); break;
            case 3: checkTwoDicts(); break;
            case 4: exit(0);
            default: std::cout << defaultPhrase; break;
            }
        }
    }

    void actWithDict(DictEngRus& dictionary) {
        size_t com = menuCom;
        while (com) {
            std::cout << actWithDictPhrase;
            helpInSize(std::cin, com);
            switch (com) {
            case 1: checkInsert(dictionary); break;
            case 2: checkDelete(dictionary); break;
            case 3: checkSearch(dictionary); break;
            case 4: checkOneWord(dictionary); break;
            case 5: writeToFile(dictionary); break;
            case 6: return;
            default: std::cout << defaultPhrase; break;
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

        size_t com = menuCom;
        while (com) {
            std::cout << checkTwoDictsPhrase;
            helpInSize(std::cin, com);
            switch (com) {
            case 1: checkMerge(dictionary1, dictionary2); break;
            case 2: checkEqual(dictionary1, dictionary2); break;
            case 3: return;
            default: std::cout << defaultPhrase; break;
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
        size_t com = menuCom;
        while (com) {
            std::cout << checkInsertPhrase;
            helpInSize(std::cin, com);
            switch (com) {
            case 1: insertOneWord(dictionary); break;
            case 2: insertManyWords(dictionary); break;
            case 3: insertOneTranslate(dictionary); break;
            case 4: insertManyTranslate(dictionary); break;
            case 5: changeTranslate(dictionary); break;
            case 6: return;
            default: std::cout << defaultPhrase; break;
            }
        }
    }
    void insertOneWord(DictEngRus& dictionary) {
        dictionary.insertWord(helpInWord(std::cin, insertEngWord, true));
        std::cout << dictionary;
        return;
    }
    void insertManyWords(DictEngRus& dictionary) {
        std::cout << insertEngWord << whenStop;
        std::string newWord;
        while (std::cin) {
            enterWord(std::cin, newWord);
            if (newWord == "x" || newWord == "÷") {
                break;
            }
            dictionary.insertWord(newWord);
        }
        std::cout << dictionary;
        return;
    }
    void insertOneTranslate(DictEngRus& dictionary) {
        std::string newWord = helpInWord(std::cin, engWordForTransl, true);
        std::string newTransl = helpInWord(std::cin, insertRussianWord, false);
        dictionary.insertTranslate(newWord, newTransl);
        std::cout << dictionary;
        return;
    }
    void insertManyTranslate(DictEngRus& dictionary) {
        std::string newWord = helpInWord(std::cin, engWordForTransl, true);
        dictSet list;
        readManyTransl(std::cin, list);
        dictionary.insertManyTransl(newWord, list);
        std::cout << dictionary;
        return;
    }

    void changeTranslate(DictEngRus& dictionary) {
        std::string newWord = helpInWord(std::cin, engWordForTransl, true);
        dictSet list;
        readManyTransl(std::cin, list);
        dictionary.changeAllTransl(newWord, list);
        std::cout << dictionary;
        return;
    }

    void checkDelete(DictEngRus& dictionary) {
        size_t com = menuCom;
        while (com) {
            std::cout << checkDeletePhrase;
            helpInSize(std::cin, com);
            switch (com) {
            case 1: checkOneWordDelete(dictionary); break;
            case 2: checkOneTranslDelete(dictionary); break;
            case 3: checkAllTranslDelete(dictionary); break;
            case 4: return;
            default: std::cout << defaultPhrase; break;
            }
        }
    }
    void checkOneWordDelete(DictEngRus& dictionary) {
        std::cout << dictionary;
        dictionary.deleteWord(helpInWord(std::cin, deleteEngWord, true));
        std::cout << dictionary;
        return;
    }
    void checkOneTranslDelete(DictEngRus& dictionary) {
        std::cout << dictionary;
        std::string word = helpInWord(std::cin, deleteEngWord, true);
        std::string delTransl = helpInWord(std::cin, deleteTransl, false);
        dictionary.deleteTranslate(word, delTransl);
        std::cout << dictionary;
        return;
    }
    void checkAllTranslDelete(DictEngRus& dictionary) {
        std::cout << dictionary;
        dictionary.deleteAllTransl(helpInWord(std::cin, deleteWordAllTransl, true));
        std::cout << dictionary;
        return;
    }

    void checkSearch(DictEngRus& dictionary) {
        std::cout << dictionary;
        std::cout << (dictionary.searchWord(helpInWord(std::cin, searchWord, true)) ?
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
        std::string word = helpInWord(std::cin, infoWord, true);
        std::cout << "\nInfo about word '" << word << "' :";
        std::cout << "\n\tTranslations: " << dictionary.getTranslate(word);
        std::cout << "\n\tCount of translations: " << dictionary.getTranslCount(word);
        std::cout << "\n\tCount of words on dictionary: " << dictionary.getCountOfWord();
        return;
    }
}
