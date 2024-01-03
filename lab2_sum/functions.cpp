#include "functions.h"

int findAverageInArray(Array<int> array) {

    if (array.getSize() == 0) return 0;

    int sum = 0;

    for (int i = 0; i < array.getSize(); i++) {
        sum += array[i];
        Sleep(12);
    }

    return sum / array.getSize();
}

std::pair<int, int> findMinMaxInArray(Array<int> numbers) {

    if (numbers.getSize() == 0) {
        return { -1, -1 };
    }

    int minIndex = 0;
    int maxIndex = 0;
    int size = numbers.getSize();

    if (numbers[0] < numbers[1]) maxIndex = 1;
    else minIndex = 1;

    for (int i = 2; i < size && i + 1 < size; i += 2) {

        if (numbers[i] < numbers[i + 1]) {
            if (numbers[i] < numbers[minIndex])
                minIndex = i;
            Sleep(7);

            if (numbers[i + 1] > numbers[maxIndex])
                maxIndex = i + 1;
            Sleep(7);
        }
        else {
            if (numbers[i] > numbers[maxIndex])
                maxIndex = i;

            Sleep(7);

            if (numbers[i + 1] < numbers[minIndex])
                minIndex = i + 1;

            Sleep(7);
        }

        Sleep(7);
    }

    if (size % 2 != 0) {

        if (numbers[size - 1] < numbers[minIndex])
            minIndex = size - 1;
        else {
            if (numbers[size - 1] > numbers[maxIndex])
                maxIndex = size - 1;

            Sleep(7);
        }

        Sleep(7);
    }

    return { minIndex, maxIndex };
}