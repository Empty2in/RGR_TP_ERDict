#include <ostream>
#include <algorithm>
#include <iomanip>
#include <functional>
#include <memory>

#include "DictEngRus.h"
#include "StreamGuard.h"
#include "AddOperators.h"

namespace elina {

	dictSet* DictEngRus::getTranslSet(const std::string& word) {
		if (!searchWord(word)) {
			return nullptr;
		}
		return &(dict_.at(word));
	}
	dictSet DictEngRus::getTranslate(const std::string& word) const {
		if (!searchWord(word)) {
			return dictSet();
		}
		return dict_.at(word);
	}

	size_t DictEngRus::getTranslCount(const std::string& word) const {
		return getTranslate(word).size();
	}
	size_t DictEngRus::getCountOfWord() const {
		return dict_.size();
	}

	bool DictEngRus::searchWord(const std::string& word) const {
		return (dict_.find(word) != dict_.end());
	}
	bool DictEngRus::insertWord(const std::string& word, const dictSet& transl) {
		auto newWord = dict_.insert( { word, transl } );
		return newWord.second;
	}
	bool DictEngRus::insertTransl(const std::string& word, dictSet transl) {
		dictSet* oldTransl = getTranslSet(word);
		if (oldTransl && !transl.empty()) {
			oldTransl->merge(transl);
			return (*oldTransl != transl);
		}
		return false;
	}
	bool DictEngRus::deleteWord(const std::string& word) {
		auto del = dict_.erase(word);
		return static_cast< bool >(del);
	}
	bool DictEngRus::deleteAllTransl(const std::string& word) {
		dictSet* delTransl = getTranslSet(word);
		if (delTransl) {
			delTransl->clear();
			return true;
		}
		return false;
	}
	bool DictEngRus::deleteTranslate(const std::string& word, const std::string& delTrans) {
		dictSet* transl = getTranslSet(word);
		if (!delTrans.empty() && transl) {
			auto del = transl->erase(delTrans);
			return static_cast< bool >(del);
		}
		return false;
	}
	bool DictEngRus::changeAllTransl(const std::string& word, const dictSet& transl) {
		if (!transl.empty() && searchWord(word)) {
			dict_.insert_or_assign(word, transl);
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
		std::swap(dict_, other.dict_);
	}
	bool DictEngRus::isEqual(const DictEngRus& other) const {
		return (dict_ == other.dict_);
	}
	bool DictEngRus::merge(DictEngRus& other) {
		dict_.merge(other.dict_);
		return (!this->isEqual(other));
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
