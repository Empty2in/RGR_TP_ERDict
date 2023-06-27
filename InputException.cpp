#include "InputException.h"

namespace elina {

	IncorrectFile::IncorrectFile() : reason_("incorrrect name of file.") {}
	const char* IncorrectFile::what() const { return reason_; }

	EmptyFile::EmptyFile() : reason_("file is empty.") {}
	const char* EmptyFile::what() const { return reason_; }
	
	WrongDictName::WrongDictName() : reason_("wrong word.") {}
	const char* WrongDictName::what() const { return reason_; }
	
}
