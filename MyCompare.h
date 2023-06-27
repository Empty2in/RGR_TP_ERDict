#ifndef MYCOMPARE_h
#define MYCOMPARE_h

#include <string>

namespace elina {
	void toLowerStr(std::string& word);
	struct dictComp {
		bool operator()(std::string word1, std::string word2) const;
	};
}
#endif
