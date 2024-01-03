#pragma once

#include "pch.h"
#include "CppUnitTest.h"

#include <vector>

//#include "..\lab2_sum\functions.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AverageMinMaxTesting
{
	TEST_CLASS(AverageMinMaxTesting)
	{
	public:
		
		TEST_METHOD(TestAverage)
		{
			std::vector<int> a = {1, 2, 3, 4};
			//Array<int> array(a);

			//int dop = findAverageInArray(array);

			Assert::AreEqual(2, a[1]);
		}
	};
}
