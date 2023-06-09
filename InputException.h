#ifndef INPUTEXCEPTION_H
#define INPUTEXCEPTION_H
#include <exception>

namespace elina {

	class IncorrectFile : public std::exception {
	public:
		IncorrectFile();
		const char* what() const;
	private:
		const char* reason_;
	};

	class EmptyFile : public std::exception {
	public:
		EmptyFile();
		const char* what() const;
	private:
		const char* reason_;
	};

	class WrongDictName : public std::exception {
	public:
		WrongDictName();
		const char* what() const;
	private:
		const char* reason_;
	};
}

#endif