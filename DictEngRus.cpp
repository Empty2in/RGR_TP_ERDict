#include "DictEngRus.h"
#include "StreamGuard.h"
#include "AddOperators.h"
#include <ostream>
#include <algorithm>
#include <iomanip>

namespace elina {

	dictPair DictEngRus::searchNode(std::string word) {
		auto ans = this->dict_.find(word);
		if (ans != this->dict_.end()) {
			return *ans;
		}
		return dictPair();
	}

	dictSet* DictEngRus::getTranslSet(std::string word) {
		if (!searchWord(word)) {
			return nullptr;
		}
		return &(this->dict_.at(word));
	}

	DictEngRus::DictEngRus() :
		dict_()
	{}

	DictEngRus::~DictEngRus() {
		this->clear();
	}

	DictEngRus::DictEngRus(const DictEngRus& other) {
		this->dict_ = other.dict_;
	}

	DictEngRus::DictEngRus(DictEngRus&& other) noexcept {
		this->dict_ = other.dict_;
		other.~DictEngRus();
	}

	DictEngRus& DictEngRus::operator=(const DictEngRus& other) {
		if (this != &other) {
			DictEngRus temp(other);
			swap(temp);
		}
		return *this;
	}

	DictEngRus& DictEngRus::operator=(DictEngRus&& other) noexcept {
		if (this != &other) {
			swap(other);
		}
		return *this;
	}

	size_t DictEngRus::getTranslCount(std::string word) const {
		return getTranslate(word).size();
	}

	size_t DictEngRus::getCountOfWord() const {
		return this->dict_.size();
	}

	dictSet DictEngRus::getTranslate(std::string word) const {
		if (!searchWord(word)) {
			return dictSet();
		}
		return this->dict_.at(word);
	}

	bool DictEngRus::searchWord(std::string word) const {
		return (this->dict_.find(word) != this->dict_.end());
	}

	void DictEngRus::insertWord(std::string word) {
		dictSet transl;
		this->dict_.insert(std::make_pair(word, transl));
	}

	void DictEngRus::insertTranslate(std::string word, std::string transl) {
		if (!searchWord(word)) {
			insertWord(word);
		}
		this->dict_.at(word).insert(transl);
		return;
	}

	void DictEngRus::insertManyTransl(std::string word, dictSet transl) {
		if (searchWord(word)) {
			dictSet* oldTransl = getTranslSet(word);
			if ((*oldTransl).empty()) {
				*oldTransl = transl;
			}
			else {
				(*oldTransl).merge(transl);
			}
		}
		this->dict_.insert(std::make_pair(word, transl));
		
		return;
	}

	void DictEngRus::deleteWord(std::string word) {
		if (searchWord(word)) {
			this->dict_.erase(word);
		}
		return;
	}


	void DictEngRus::deleteAllTransl(std::string word) {
		if (searchWord(word)) {
			dictSet* delTransl = getTranslSet(word);
			if (!(*delTransl).empty()) {
				(*delTransl).clear();
			}
		}
	}

	void DictEngRus::deleteTranslate(std::string word, std::string delTrans) {
		if (searchWord(word)) {
			dictSet* transl = getTranslSet(word);
			if ((*transl).find(delTrans) != (*transl).end()) {
				(*transl).erase(delTrans);
			}
		}
	}

	void DictEngRus::changeAllTransl(std::string word, const dictSet& transl) {
		if (searchWord(word)) {
			dictSet* oldTransl = getTranslSet(word);
			if (!(*oldTransl).empty()) {
				(*oldTransl).clear();
			}
			*oldTransl = transl;
		}
	}

	void DictEngRus::clear() {
		if (!isEmpty()) {
			this->dict_.clear();
		}
	}

	bool DictEngRus::isEmpty() const {
		return this->dict_.empty();
	}

	void DictEngRus::swap(DictEngRus& other) {
		std::swap(this->dict_, other.dict_);
	}

	bool DictEngRus::isEqual(const DictEngRus& other) const {
		return (this->dict_ == other.dict_);
	}

	void DictEngRus::merge(DictEngRus& other) {
		this->dict_.merge(other.dict_);
	}

	std::ostream& operator <<(std::ostream& out, const DictEngRus& tree) {
		std::ostream::sentry sentry(out);
		if (!sentry) {
			return out;
		}
		StreamGuard stream(out);
		out << "DICTIONARY:\n";
		std::for_each(
			tree.dict_.cbegin(),
			tree.dict_.cend(),
			[&out](const dictPair& it)
			{ out << it; }
		);
		return out;
	}

}
