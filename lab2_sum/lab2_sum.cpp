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
    double min = 0;
    double max = 0;
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

    double prevMin = min(numbers[0], numbers[1]);
    double prevMax = max(numbers[0], numbers[1]);

    for (int i = 2; i < info->cntNum && i + 1 < info->cntNum; i += 2) {
        
        prevMin = min(prevMin, min(numbers[i], numbers[i + 1]));
        prevMax = max(prevMax, max(numbers[i], numbers[i + 1]));

        Sleep(7);
    }

    if (info->cntNum % 2 != 0) {
        prevMin = min(prevMin, numbers[info->cntNum - 1]);
        prevMax = max(prevMax, numbers[info->cntNum - 1]);
    }

    static_cast<funcArgument*>(arg)->min = prevMin;
    static_cast<funcArgument*>(arg)->max = prevMax;

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
                    generalArg->min << " and " << generalArg->max << std::endl;
    
    return 0;
}