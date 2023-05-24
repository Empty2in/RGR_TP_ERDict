#ifndef MYCOMPARE_h
#define MYCOMPARE_h

#include <iostream>

namespace elina {
	std::string toLowerStr(std::string& word);
	struct dictComp {
		bool operator()(std::string word1, std::string word2) const;
	};
}
#endif
