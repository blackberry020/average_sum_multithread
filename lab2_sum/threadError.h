#pragma once
#include <iostream>

class ThreadError : public std::exception
{
public:
    ThreadError(const std::string& message) : message{ message }
    {}

    const char* what() const noexcept override
    {
        return message.c_str();
    }
private:
    std::string message;
};
