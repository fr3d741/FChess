#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

enum ErrorCodes
{
    NETWORK_ERROR
};

class NetworkException : public std::exception
{
public:
    NetworkException();
};

#endif // EXCEPTIONS_H
