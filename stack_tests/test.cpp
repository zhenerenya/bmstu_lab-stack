#include "pch.h"
#include "../Stack.h"

#include<type_traits>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}
TEST(Test_stack, Test_head) {
	Stack<int>st;
	EXPECT_ANY_THROW(st.head());
}
TEST(Test_stack, Test_push) {
	Stack<int>st;
	st.push(1);
	EXPECT_EQ(st.head(), 1);
}
TEST(Test_stack, Test_pop) {
	Stack<int>st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	EXPECT_EQ(st.head(), 4);
	st.pop();
	EXPECT_EQ(st.head(), 3);
}
TEST(Test_stack, Test_push_emplace) {
	Stack<int>st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push_emplace(10, 11, 12, 13, 14, 15);
	EXPECT_EQ(st.head(), 15);
}
TEST(Test_stack, Test_pop_) {
	Stack<int>st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	EXPECT_EQ(st.head(), 4);
	int a = st._pop();
	EXPECT_EQ(a, 4);
	EXPECT_EQ(st.head(), 3);
}

TEST(Test_stack, Test_is_move) {
	ASSERT_EQ(std::is_move_constructible<Stack<int>>::value, true);
	ASSERT_EQ(std::is_move_assignable<Stack<int>>::value, true);
}

TEST(Test_stack, Test_is_copy) {
	ASSERT_EQ(std::is_copy_constructible<Stack<int>>::value, false);
	ASSERT_EQ(std::is_copy_assignable<Stack<int>>::value, false);
}
