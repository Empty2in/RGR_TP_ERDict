#ifndef ADDSTRUCRS_H
#define ADDSTRUCTS_H

#include <iosfwd>
#include <set>

#include "MyCompare.h"

namespace elina {

	struct dictWord {
		std::string word_;
	};
	struct dictName {
		std::string dictName_;
	};
	struct trans {
		std::string word_;
	};
	struct translist {
		std::set< std::string, dictComp > list_;
	};
	struct dictStr {
		std::string word_;
		std::set< std::string, dictComp > list_;
	};

	bool checkWord(const std::string& word);
	std::istream& operator>>(std::istream& in, dictName& word);
	std::istream& operator>>(std::istream& in, dictWord& word);
	std::istream& operator>>(std::istream& in, dictStr& str);
	std::istream& operator>>(std::istream& in, trans& word);
	std::istream& operator>>(std::istream& in, translist& list);

}

#endif
