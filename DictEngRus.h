#ifndef DICTENGRUS_H
#define DICTENGRUS_H

#include <map>
#include <set>
#include <string>

namespace elina {

	using dictMap = std::map< std::string, std::set< std::string > >;
	using dictPair = std::pair< std::string, std::set< std::string > >;
	using dictSet = std::set< std::string >;
	using dictMapIter = std::map< std::string, std::set< std::string > >::iterator;

	class DictEngRus {
	private:
		dictMap dict_;

		dictPair searchNode(std::string word);
		dictSet* getTranslSet(std::string word);

	public:
		DictEngRus();
		~DictEngRus();
		DictEngRus(const DictEngRus& other);
		DictEngRus(DictEngRus&& other) noexcept;
		DictEngRus& operator=(const DictEngRus& other);
		DictEngRus& operator=(DictEngRus&& other) noexcept;

		void clear();
		bool isEmpty() const;
		void swap(DictEngRus& other);

		size_t getCountOfWord() const;
		size_t getTranslCount(std::string word) const;
		dictSet getTranslate(std::string word) const;

		bool searchWord(std::string word) const;

		void insertWord(std::string word);
		void insertTranslate(std::string word, std::string transl);
		void insertManyTransl(std::string word, dictSet transl);
		
		void deleteWord(std::string word);
		void deleteAllTransl(std::string word);
		void deleteTranslate(std::string word, std::string delTrans);

		void changeAllTransl(std::string word, const dictSet& transl);

		bool isEqual(const DictEngRus& other) const;
		void merge(DictEngRus& other);

		friend std::ostream& operator<<(std::ostream& out, const DictEngRus& tree);
	};

}

#endif

