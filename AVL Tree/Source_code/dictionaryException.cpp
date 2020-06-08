#include "dictionaryException.h"

DictionaryException::DictionaryException(std::string message) : message(message)
{

}

std::string DictionaryException::get_message()
{
	return message;
}