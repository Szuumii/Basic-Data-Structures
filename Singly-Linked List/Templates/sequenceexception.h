#ifndef SEQUENCEEXCEPTION_H
#define SEQUENCEEXCEPTION_H

#include <exception>
#include <string>

class SequenceException : public std::exception
{
    std::string message;

public:
    SequenceException(std::string message);
    std::string get_message();

};
#endif
