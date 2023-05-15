#ifndef ADDOPERATORS_H
#define ADDOPERATORS_H

#include <set>
#include <map>
#include <string>
#include <fstream>
#include "DictEngRus.h"

namespace elina {

	void openFile(std::fstream& in, std::string& fileName);
	void readDictFromFail(std::fstream& in, DictEngRus& dictionary);
	void readManyTransl(std::istream& in, DictEngRus& dictionary);
	void creatFileDict(DictEngRus& dictionary);
	bool checkWord(std::string word);
	std::string enterWord(std::istream& in);

	void mainMenu();
	void actWithDict(DictEngRus& dictionary);

	void checkEmptyDictionary();
	void checkFileDict();
	void checkTwoDicts();

	void checkMerge(DictEngRus& dictionary1, DictEngRus& dictionary2);
	void checkEqual(const DictEngRus& dictionary1, const DictEngRus& dictionary2);

	void checkInsert(DictEngRus& dictionary);
	void insertManyWords(DictEngRus& dictionary);
	void insertOneWord(DictEngRus& dictionary);
	void insertOneTranslate(DictEngRus& dictionary);
	void insertManyTranslate(DictEngRus& dictionary);
	void changeTranslate(DictEngRus& dictionary);

	void checkDelete(DictEngRus& dictionary);
	void checkOneWordDelete(DictEngRus& dictionary);
	void checkOneTranslDelete(DictEngRus& dictionary);
	void checkAllTranslDelete(DictEngRus& dictionary);

	void checkSearch(DictEngRus& dictionary);

	void checkOneWord(DictEngRus& dictionary);

	std::ostream& operator <<(std::ostream& out, const dictSet& st);
	std::ostream& operator <<(std::ostream& out, const dictPair& par);

}


#endif