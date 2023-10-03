#pragma once

#include "Array.h"

struct funcArgument {

    funcArgument(Array<double> _arr, int _cnt) {
        arrNumbers = _arr;
        cntNum = _cnt;
    }

    Array<double> arrNumbers;
    int cntNum = 0;

    double average = 0;
    int minIndex = 0;
    int maxIndex = 0;
};
