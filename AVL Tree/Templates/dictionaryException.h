#ifndef DICTIONARYEXCEPTION_H
#define DICTIONARYEXCEPTION_H

#include <string>

class DictionaryException final : public std::exception
{
	std::string message;

public:
	DictionaryException(std::string message);
	std::string get_message();
};
#endif // !DICTIONARYEXCEPTION_H

