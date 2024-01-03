#pragma once

#include "pch.h"
#include "CppUnitTest.h"

#include <vector>

#include "..\lab2_sum\functions.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AverageMinMaxTesting
{
	TEST_CLASS(AverageMinMaxTesting)
	{
	public:
		
		TEST_METHOD(TestAverage1)
		{
			std::vector<int> a = {1, 2, 3, 4};
			Array<int> array(a);
			Assert::AreEqual(2, findAverageInArray(array));
		}

		TEST_METHOD(TestAverage2)
		{
			std::vector<int> a = { 2, 2, 2, 2 };
			Array<int> array(a);
			Assert::AreEqual(2, findAverageInArray(array));
		}

		TEST_METHOD(TestAverageEmptyArray)
		{
			std::vector<int> a = {};
			Array<int> array(a);
			Assert::AreEqual(0, findAverageInArray(array));
		}

		TEST_METHOD(TestMinMaxEmptyArray)
		{
			std::vector<int> a = {};
			Array<int> array(a);

			std::pair<int, int> result = findMinMaxInArray(array);

			Assert::AreEqual(-1, result.first);
			Assert::AreEqual(-1, result.second);
		}

		TEST_METHOD(TestMinMax1)
		{
			std::vector<int> a = {4, 5, 1, 2, 6, 2};
			Array<int> array(a);

			std::pair<int, int> result = findMinMaxInArray(array);

			Assert::AreEqual(1, array[result.first]);
			Assert::AreEqual(6, array[result.second]);
		}

		TEST_METHOD(TestMinMax2)
		{
			std::vector<int> a = { 1, 5, 4, 2, 3, 6 };
			Array<int> array(a);

			std::pair<int, int> result = findMinMaxInArray(array);

			Assert::AreEqual(1, array[result.first]);
			Assert::AreEqual(6, array[result.second]);
		}
	};
}
