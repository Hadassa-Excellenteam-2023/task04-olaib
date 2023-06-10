#pragma once
#include <exception>

class MyException : public std::exception
{
public:
    MyException(const char* msg) : std::exception(msg) {}

    const char* what() const noexcept override
    {
        return std::exception::what();
    }

    ~MyException() override = default;

};

class FileError : public MyException
{
public:
    FileError(const char* msg) :MyException(msg) {}
};

