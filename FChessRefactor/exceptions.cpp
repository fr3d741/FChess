#include <iostream>
#include "exceptions.h"

NetworkException::NetworkException()
{
}


InvalidArgumentException::InvalidArgumentException(const char *msg)
{
    std::cerr << msg << std::endl;
}
