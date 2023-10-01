#include <iostream>
#include <windows.h>

struct funcArgument {
    double* arrNumbers = nullptr;
    int cntNum = 0;

    double average = 0;
    double min = 0;
    double max = 0;
};

DWORD WINAPI findAverage(LPVOID arg)
{
    std::cout << "Average thread is started." << std::endl;

    double sum = 0;
    funcArgument* info = static_cast<funcArgument*>(arg);

    double* numbers = info->arrNumbers;

    for (int i = 0; i < info->cntNum; i++) {
        sum += numbers[i];
        Sleep(12);
    }

    static_cast<funcArgument*>(arg)->average = sum / info->cntNum;

    std::cout << "Average thread is finished." << std::endl;

    return 0;
}

DWORD WINAPI findMinMax(LPVOID arg)
{
    std::cout << "MinMax thread is started." << std::endl;

    funcArgument* info = static_cast<funcArgument*>(arg);
    double* numbers = info->arrNumbers;

    double prevMin = min(numbers[0], numbers[1]);
    double prevMax = max(numbers[0], numbers[1]);

    for (int i = 2; i < info->cntNum && i + 1 < info->cntNum; i += 2) {
        
        prevMin = min(prevMin, min(numbers[i], numbers[i + 1]));
        prevMax = max(prevMax, max(numbers[i], numbers[i + 1]));

        Sleep(12);
    }

    if (info->cntNum % 2 != 0) {
        prevMin = min(prevMin, numbers[info->cntNum - 1]);
        prevMax = max(prevMax, numbers[info->cntNum - 1]);
    }

    static_cast<funcArgument*>(arg)->min = 0;
    static_cast<funcArgument*>(arg)->max = 0;

    std::cout << "MinMax thread is finished." << std::endl;

    return 0;
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

    HANDLE hAverageThread;
    DWORD IDaverageThread;

    funcArgument* generalArg = new funcArgument();
    generalArg->arrNumbers = numbers;
    generalArg->cntNum = n;
    
    hAverageThread = CreateThread(NULL, 0, findAverage, (void*)generalArg, 0, &IDaverageThread);

    if (hAverageThread == NULL) {
        std::cout << "could not create a thread for sum";
        return GetLastError();
    }

    WaitForSingleObject(hAverageThread, INFINITE);

    CloseHandle(hAverageThread);

    std::cout << "The average of given numbers is " << generalArg->average << std::endl;
    
    return 0;
}