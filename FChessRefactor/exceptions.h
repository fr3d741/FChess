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

class InvalidArgumentException : public std::exception
{
public:
    InvalidArgumentException(const char* msg);
};

#endif // EXCEPTIONS_H
