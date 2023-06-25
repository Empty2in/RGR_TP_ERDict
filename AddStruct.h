#ifndef ADDSTRUCRS_H
#define ADDSTRUCTS_H

#include "MyCompare.h"
#include <iostream>
#include <set>

namespace elina {

	struct dictWord {
		std::string word_;
	};
	struct dictName {
		std::string word_;
	};
	struct fileWord {
		std::string word_;
	};
	struct readSet {
		std::set< std::string, dictComp > list_;
	};
	struct dictStr {
		std::string word_;
		std::set< std::string, dictComp > list_;
	};

	bool checkWord(std::string word);
	std::istream& operator>>(std::istream& in, dictName& word);
	std::istream& operator>>(std::istream& in, dictWord& word);
	std::istream& operator>>(std::istream& in, dictStr& str);
	std::istream& operator>>(std::istream& in, fileWord& word);
	std::istream& operator>>(std::istream& in, readSet& list);

}

#endif
