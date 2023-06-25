#ifndef ADDOPERATORS_H
#define ADDOPERATORS_H

#include "DictEngRus.h"
#include <set>
#include <map>
#include <string>
#include <fstream>

namespace elina {

	void openFile(std::fstream& in);
	std::string helpInWord(std::istream& in);
	void writeToFile(DictEngRus& dictionary);
	void creatFileDict(DictEngRus& dictionary);
	void readDictFromFile(std::fstream& in, DictEngRus& dictionary);

	void mainMenu();
	void actWithDict(DictEngRus& dictionary);

	void checkEmptyDictionary();
	void checkFileDict();

	void merge(DictEngRus& dictionary);
	void equal(const DictEngRus& dictionary);

	void insertWord(DictEngRus& dictionary);
	void addTransl(DictEngRus& dictionary);
	void changeTranslate(DictEngRus& dictionary);

	void deleted(DictEngRus& dictionary);
	void oneWordDelete(DictEngRus& dictionary);
	void oneTranslDelete(DictEngRus& dictionary);
	void allTranslDelete(DictEngRus& dictionary);

	void search(const DictEngRus& dictionary);
	void info(const DictEngRus& dictionary);

	std::ostream& operator <<(std::ostream& out, const dictSet& st);
	std::ostream& operator <<(std::ostream& out, const dictPair& par);
	std::ostream& operator <<(std::ostream& out, const DictEngRus& tree);
}

#endif