#include "ringexception.h"

RingException::RingException(std::string message) : message(message)
{

}

std::string RingException::get_message()
{
	return message;
}