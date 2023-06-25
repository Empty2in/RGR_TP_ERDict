#ifndef DICTENGRUS_H
#define DICTENGRUS_H

#include "MyCompare.h"

#include <map>
#include <set>
#include <string>

namespace elina {
	using dictMap = std::map< std::string, std::set< std::string, dictComp >, dictComp >;
	using dictPair = std::pair< std::string, std::set< std::string, dictComp > >;
	using dictSet = std::set< std::string, dictComp >;
	using dictMapIter = std::map< std::string, std::set< std::string, dictComp >, dictComp >::iterator;
	using dictMapCIter= std::map< std::string, std::set< std::string, dictComp >, dictComp >::const_iterator;

	class DictEngRus {

	public:
		DictEngRus() = default;
		~DictEngRus() = default;
		DictEngRus(const DictEngRus& other) = default;
		DictEngRus(DictEngRus&& other) noexcept = default;

		dictMapIter begin();
		dictMapIter end();
		dictMapCIter cbegin() const;
		dictMapCIter cend() const;

		void clear();
		bool isEmpty() const;
		void swap(DictEngRus& other) noexcept;

		size_t getCountOfWord() const;
		size_t getTranslCount(const std::string& word) const;
		dictSet getTranslate(const std::string& word) const;

		bool searchWord(const std::string& word) const;

		bool insertWord(const std::string& word, const dictSet transl = dictSet{});
		bool insertTransl(const std::string& word, dictSet transl);
		
		bool deleteWord(const std::string& word);
		bool deleteAllTransl(const std::string& word);
		bool deleteTranslate(const std::string& word, const std::string& delTrans);

		bool changeAllTransl(const std::string& word, const dictSet& transl);

		bool isEqual(const DictEngRus& other) const;
		bool merge(DictEngRus& other);

	private:
		dictMap dict_;
		dictSet* getTranslSet(const std::string& word);
	};
}

#endif

