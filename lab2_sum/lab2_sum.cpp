#pragma once

#include <windows.h>
#include <boost/lexical_cast.hpp>

#include "threadError.h"
#include "funcArgument.h"
#include "Array.h"

#include "functions.h"

DWORD WINAPI findAverage(LPVOID arg)
{
    int sum = 0;
    funcArgument* info = static_cast<funcArgument*>(arg);

    Array<int> numbers = info->arrNumbers;
    static_cast<funcArgument*>(arg)->average = findAverageInArray(numbers);

    return 0;
}

DWORD WINAPI findMinMax(LPVOID arg)
{
    funcArgument* info = static_cast<funcArgument*>(arg);

    Array<int> numbers = info->arrNumbers;
    std::pair<int, int> minMax = findMinMaxInArray(numbers);

    static_cast<funcArgument*>(arg)->minIndex = minMax.first;
    static_cast<funcArgument*>(arg)->maxIndex = minMax.second;

    return 0;
}

void startThread(funcArgument* arg, void* funcToCall) {

    HANDLE hThread;
    DWORD IDThread;

    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)funcToCall, (void*)arg, 0, &IDThread);

    if (hThread == NULL) {
        throw ThreadError("could not create a thread with id " + boost::lexical_cast<std::string>(IDThread));
    }

    WaitForSingleObject(hThread, INFINITE);

    CloseHandle(hThread);
}

int main()
{
    int n;

    std::cout << "Enter the amount of numbers" << std::endl;
    std::cin >> n;

    Array<int> numbers(n);

    std::cout << "Enter your numbers" << std::endl;

    numbers.readArray();

    funcArgument* generalArg = new funcArgument(numbers, n);

    try {
        startThread(generalArg, findAverage);
    }
    catch (const ThreadError& err) {
        std::cout << err.what() << std::endl;
        return -1;
    }

    std::cout << "The average of given numbers is " << generalArg->average << std::endl;

    try {
        startThread(generalArg, findMinMax);
    }
    catch (const ThreadError& err) {
        std::cout << err.what() << std::endl;
        return -1;
    }

    std::cout << "The min and max elements of given numbers are " << 
                    numbers[generalArg->minIndex] << " and " << numbers[generalArg->maxIndex] << std::endl;

    numbers[generalArg->minIndex] = generalArg->average;
    numbers[generalArg->maxIndex] = generalArg->average;

    std::cout << "Your numbers after replacing min and max with average: " << std::endl;

    numbers.printArray();

    std::cout << std::endl;
    
    return 0;
}