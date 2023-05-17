#ifndef ADDSTRUCRS_H
#define ADDSTRUCTS_H

#include <iostream>
namespace elina {
	std::string toLowerStr(std::string& word);

	struct dictComp {
		bool operator()(std::string word1, std::string word2) const;
	};
}


#endif
