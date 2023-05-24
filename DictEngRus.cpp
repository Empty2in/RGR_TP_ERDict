#include "DictEngRus.h"
#include "StreamGuard.h"
#include "AddOperators.h"
#include <ostream>
#include <algorithm>
#include <iomanip>
#include <functional>
#include <memory>

namespace elina {

	dictSet* DictEngRus::getTranslSet(const std::string& word) {
		if (!searchWord(word)) {
			return nullptr;
		}
		return &(this->dict_.at(word));
	}

	size_t DictEngRus::getTranslCount(const std::string& word) const {
		return getTranslate(word).size();
	}

	size_t DictEngRus::getCountOfWord() const {
		return dict_.size();
	}

	dictSet DictEngRus::getTranslate(const std::string& word) const {
		if (!searchWord(word)) {
			return dictSet();
		}
		return dict_.at(word);
	}

	bool DictEngRus::searchWord(const std::string& word) const {
		return (dict_.find(word) != dict_.end());
	}

	bool DictEngRus::insertWord(const std::string& word) {
		dictSet transl;
		auto newWord = dict_.insert(std::make_pair(word, transl));
		return static_cast<bool>(newWord.second);
	}

///////////////////////////////////////
	bool DictEngRus::insertTranslate(const std::string& word, const std::string& transl) {
		if (!searchWord(word)) {
			insertWord(word);
		}
		dict_.at(word).insert(transl);
		/*dict_[word].insert(transl);*/
		return true;
	}

	bool DictEngRus::insertManyTransl(const std::string& word, dictSet transl) {
		if (!searchWord(word)) {
			dict_.insert(std::make_pair(word, transl));
			return true;
		}
		dictSet* oldTransl = getTranslSet(word);
		(*oldTransl).merge(transl);
		return true;
	}
///////////////////////////////////////

	bool DictEngRus::deleteWord(const std::string& word) {
		auto del = dict_.erase(word);
		return static_cast<bool>(del);
	}
	bool DictEngRus::deleteAllTransl(const std::string& word) {
		if (searchWord(word)) {
			dictSet* delTransl = getTranslSet(word);
			(* delTransl).clear();
			return true;
		}
		return false;
	}

	bool DictEngRus::deleteTranslate(const std::string& word, const std::string& delTrans) {
		if (searchWord(word)) {
			dictSet* transl = getTranslSet(word);
			if ((*transl).find(delTrans) != (*transl).end()) {
				(*transl).erase(delTrans);
				return true;
			}
		}
		return false;
	}

	bool DictEngRus::changeAllTransl(const std::string& word, const dictSet& transl) {
		if (searchWord(word)) {
			dictSet* oldTransl = getTranslSet(word);
			(*oldTransl).clear();
			*oldTransl = transl;
			return true;
		}
		return false;
	}

	void DictEngRus::clear() {
		dict_.clear();
	}

	bool DictEngRus::isEmpty() const {
		return dict_.empty();
	}

	void DictEngRus::swap(DictEngRus& other) noexcept {
		std::swap(this->dict_, other.dict_);
	}

	bool DictEngRus::isEqual(const DictEngRus& other) const {
		return (this->dict_ == other.dict_);
	}

	bool DictEngRus::merge(DictEngRus& other) {
		if (isEqual(other)) {
			return false;
		}
		this->dict_.merge(other.dict_);
		return true;
	}

	dictMapIter DictEngRus::begin(){
		return dict_.begin();
	}

	dictMapIter DictEngRus::end() {
		return dict_.end();
	}

	dictMapCIter DictEngRus::cbegin() const {
		return dict_.cbegin();
	}

	dictMapCIter DictEngRus::cend() const {
		return dict_.cend();
	}
}
