#include "sequenceexception.h"

SequenceException::SequenceException(std::string message): message(message)
{

}

std::string SequenceException::get_message()
{
    return message;
}
