#include <iostream>
#include <windows.h>
#include <boost/lexical_cast.hpp>

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

struct funcArgument {
    double* arrNumbers = nullptr;
    int cntNum = 0;

    double average = 0;
    int minIndex = 0;
    int maxIndex = 0;
};

DWORD WINAPI findAverage(LPVOID arg)
{
    double sum = 0;
    funcArgument* info = static_cast<funcArgument*>(arg);

    double* numbers = info->arrNumbers;

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
    double* numbers = info->arrNumbers;

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

    double* numbers = new double[n];

    std::cout << "Enter your numbers" << std::endl;

    for (int i = 0; i < n; i++) {
        std::cin >> numbers[i];
    }

    funcArgument* generalArg = new funcArgument();
    generalArg->arrNumbers = numbers;
    generalArg->cntNum = n;

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
    
    return 0;
}