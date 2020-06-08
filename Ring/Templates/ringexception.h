#ifndef RINGEXCEPTION_H
#define RINGEXCEPTION_H

#include <string>


class RingException final : public std::exception
{
	std::string message;

public:
	RingException(std::string message);
	std::string get_message();

};
#endif // RINGEXCEPTION_H

