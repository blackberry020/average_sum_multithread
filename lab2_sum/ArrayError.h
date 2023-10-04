#pragma once
#include <iostream>

class ArrayError : public std::exception
{
public:
    ArrayError(const std::string& message) : message{ message }
    {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }
private:
    std::string message;
};
