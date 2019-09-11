#include "stdafx.h"
#include "CppUnitTest.h"
#include "CppUnitTestAssert.h"
#include "../data_structures/vector.h"
#include <algorithm> // is_sorted

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			std::wstring ToString(const Vector& t) {
				return ToString(t.Stringify());
			}
			std::wstring ToString(const Vector* t) {
				return ToString(t->Stringify());
			}
			std::wstring ToString(Vector* t) {
				return ToString(t->Stringify());
			}
		}
	}
}


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace VectorUnitTests
{		
	TEST_CLASS(VectorUnitTests)
	{
	public:
		TEST_METHOD(TestVectorCopyCtor) {
			Vector base({ 69, 420, 666 });
			Vector copy(base);
			Assert::AreEqual(base, copy);
		}

		TEST_METHOD(TestVectorDeepCopy) {
			Vector base({ 69, 420, 666 });
			Vector copy(base);
			copy.PushBack(1917);
			Assert::AreNotEqual(base, copy);
		}

		TEST_METHOD(TestVectorArrayCtor) {
			Vector my_vec({ 1 });
			Assert::AreEqual(1, my_vec[0]);
		}

		TEST_METHOD(TestVectorEqual) {
			Vector my_vec({ 1, 2, 3, 4, 5 });
			Vector my_vec2({ 1, 2, 3, 4, 5 });
			Assert::AreEqual(my_vec, my_vec2);
		}

		TEST_METHOD(TestVectorAssign) {
			Vector base({ 69, 420, 666 });
			Vector assigned;
			assigned = base;
			Assert::AreEqual(base, assigned);
		}

		TEST_METHOD(TestVectorCapacity) {
			Vector my_vec;
			bool size_exceeds_capacity = my_vec.get_size() > my_vec.get_capacity();
			Assert::IsFalse(size_exceeds_capacity);
		}

		TEST_METHOD(TestVectorSize) {
			const std::initializer_list<int> kInitList({ 69, 420, 666 });
			Vector base(kInitList);
			Assert::AreEqual(kInitList.size(), base.get_size());
		}

		TEST_METHOD(TestVectorClear) {
			Vector my_vec({ 69, 420, 666 });
			my_vec.Clear();
			Assert::AreEqual(0u, my_vec.get_size());
		}

		TEST_METHOD(TestVectorInsert) {
			Vector base({ 69, 420, 666 });
			base.Insert(1917, 0);
			Assert::AreEqual(Vector({ 1917, 69, 420, 666 }), base);
		}

		TEST_METHOD(TestVectorInsertIncreasesSize) {
			Vector base({ 69, 420, 666 });
			const auto kStartingSize = base.get_size();
			const auto kIncreaseBy = kStartingSize;
			for (unsigned int i = 0; i < kIncreaseBy; ++i) {
				base.Insert(1917, base.get_size() - 1);
			}
			Assert::AreEqual(kStartingSize + kIncreaseBy, base.get_size());
		}

		TEST_METHOD(TestVectorInsertExpandsCapacity) {
			Vector base({ 69, 420, 666 });
			auto starting_capacity = base.get_capacity();
			auto empty_space = starting_capacity - base.get_size();
			for (unsigned int i = 0; i <= empty_space; ++i) {
				base.Insert(1917, 0);
			}
			bool capacity_didnt_expand = base.get_capacity() <= starting_capacity;
			Assert::IsFalse(capacity_didnt_expand);
		}

		TEST_METHOD(TestVectorPush) {
			Vector my_vec;
			auto value = 1;
			my_vec.PushBack(value);
			Assert::AreEqual(value, my_vec[0]);
		}

		TEST_METHOD(TestVectorPushIncreasesSize) {
			Vector my_vec({ 69, 420, 666 });
			const auto kStartingSize = my_vec.get_size();
			const auto kIncreaseBy = kStartingSize;
			for (unsigned int i = 0; i < kIncreaseBy; ++i) {
				my_vec.PushBack(1917);
			}
			Assert::AreEqual(kStartingSize + kIncreaseBy, my_vec.get_size());
		}


		TEST_METHOD(TestVectorPushExpandsCapacity) {
			Vector my_vec;
			const auto starting_capacity = my_vec.get_capacity();
			const auto empty_space = starting_capacity - my_vec.get_size();
			for (unsigned int i = 0; i <= empty_space; ++i) {
				my_vec.PushBack(i);
			}
			bool capacity_didnt_expand = my_vec.get_capacity() <= starting_capacity;
			Assert::IsFalse(capacity_didnt_expand);
		}

		TEST_METHOD(TestVectorPopGetsLastElement) {
			const int kLastElement = 666;
			Vector base({ 69, 420, kLastElement });
			Assert::AreEqual(kLastElement, base.PopBack());
		}

		TEST_METHOD(TestVectorPopDecreasesSize) {
			Vector my_vec;
			unsigned int starting_size = 32;
			for (unsigned int i = 0; i < starting_size; i++) {
				my_vec.PushBack(i);
			}
			unsigned int new_size = starting_size / 2;
			for (unsigned int i = 0; i < starting_size - new_size; i++) {
				my_vec.PopBack();
			}

			Assert::AreEqual(new_size, my_vec.get_size());
		}

		TEST_METHOD(TestVectorInsertionSort) {
			Vector unsorted_vector({ 420, 69, 666 });
			Vector sorted_vector = InsertionSort(unsorted_vector);
			Assert::IsTrue(std::is_sorted(sorted_vector.begin(), sorted_vector.end()));
		}

		// instinct is to write some tests to ensure it handles empty and one length arrays
		// but there doesn't appear to be a convienient way to write that

		TEST_METHOD(TestVectorMergeSort) {
			Vector unsorted_vector({ 420, 69, 1917, 666, 5, 4, 3, 2, 1 });
			Vector sorted_vector = MergeSort(unsorted_vector);
			Assert::IsTrue(std::is_sorted(sorted_vector.begin(), sorted_vector.end()));
		}
	};
}