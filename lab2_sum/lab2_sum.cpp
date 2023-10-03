#include <windows.h>
#include <boost/lexical_cast.hpp>

#include "threadError.h"
#include "funcArgument.h"
#include "Array.h"

DWORD WINAPI findAverage(LPVOID arg)
{
    std::cout << "great" << std::endl;

    double sum = 0;
    funcArgument* info = static_cast<funcArgument*>(arg);

    Array<double> numbers = info->arrNumbers;

    for (int i = 0; i < info->cntNum; i++) {
        sum += numbers[i];
        Sleep(12);
    }

    static_cast<funcArgument*>(arg)->average = sum / info->cntNum;

    return 0;
}

DWORD WINAPI findMinMax(LPVOID arg)
{
    funcArgument* info = static_cast<funcArgument*>(arg);
    Array<double> numbers = info->arrNumbers;

    int minIndex = 0;
    int maxIndex = 0;

    if (numbers[0] < numbers[1]) maxIndex = 1;
    else minIndex = 1;

    for (int i = 2; i < info->cntNum && i + 1 < info->cntNum; i += 2) {
        
        if (numbers[i] < numbers[i + 1]) {
            if (numbers[i] < numbers[minIndex])
                minIndex = i;
            if (numbers[i + 1] > numbers[maxIndex])
                maxIndex = i + 1;
        }
        else {
            if (numbers[i] > numbers[maxIndex])
                maxIndex = i;
            if (numbers[i + 1] < numbers[minIndex])
                minIndex = i + 1;
        }

        Sleep(7);
    }

    if (info->cntNum % 2 != 0) {
        
        if (numbers[info->cntNum - 1] < numbers[minIndex])
            minIndex = info->cntNum - 1;
        else
            if (numbers[info->cntNum - 1] > numbers[maxIndex])
                maxIndex = info->cntNum - 1;
    }

    static_cast<funcArgument*>(arg)->minIndex = minIndex;
    static_cast<funcArgument*>(arg)->maxIndex = maxIndex;

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

    Array<double> numbers(n);

    std::cout << "Enter your numbers" << std::endl;

    numbers.readArray();

    funcArgument* generalArg = new funcArgument(numbers, n);

    try {
        startThread(generalArg, findAverage);
        std::cout << "still great" << std::endl;
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