#include "stdafx.h"
#include "CppUnitTest.h"
#include "../data_structures/vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorUnitTests
{		
	TEST_CLASS(VectorUnitTests)
	{
	public:
		TEST_METHOD(TestVectorArrayCtor) {
			Vector my_vec({ 1 });
			Assert::AreEqual(1, my_vec[0]);
		}


		TEST_METHOD(TestVectorPush) {
			Vector my_vec;
			auto value = 1;
			my_vec.PushBack(value);
			Assert::AreEqual(value, my_vec[0]);
		}

		TEST_METHOD(TestVectorSize) {
			Vector my_vec;
			my_vec.PushBack(1);
			unsigned int expected_size = 1;
			Assert::AreEqual(expected_size, my_vec.get_size());
		}

		TEST_METHOD(TestVectorCapacity) {
			Vector my_vec;
			bool size_exceeds_capacity = my_vec.get_size() > my_vec.get_capacity();
			Assert::IsFalse(size_exceeds_capacity);
		}

		TEST_METHOD(TestVectorCapacityIncrease) {
			Vector my_vec;
			auto free_space = my_vec.get_capacity() - my_vec.get_size();
			for (unsigned int i = 0; i <= free_space; ++i) {
				my_vec.PushBack(i);
			}
			bool size_exceeds_capacity = my_vec.get_size() > my_vec.get_capacity();
			Assert::IsFalse(size_exceeds_capacity);
		}

		TEST_METHOD(TestVectorPop) {
			Vector my_vec;
			unsigned int target_size = 32;
			for (unsigned int i = 0; i < target_size; i++) {
				my_vec.PushBack(i);
			}
			unsigned int new_size = target_size / 2;
			for (unsigned int i = 0; i < target_size - new_size; i++) {
				my_vec.PopBack();
			}

			Assert::AreEqual(new_size, my_vec.get_size());
		}

	};
}