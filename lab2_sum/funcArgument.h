#pragma once

#include "Array.h"

struct funcArgument {

    funcArgument(Array<int> _arr, int _cnt) {
        arrNumbers = _arr;
        cntNum = _cnt;
    }

    Array<int> arrNumbers;
    int cntNum = 0;

    int average = 0;
    int minIndex = 0;
    int maxIndex = 0;
};
