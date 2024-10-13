#include <gtest/gtest.h>
#include "Stack.h"

class StackTest : public ::testing::Test {
protected:

    Stack<int> createStack(std::size_t capacity, const std::vector<int>& values) {
        Stack<int> stack(capacity);
        for (const auto& val : values) {
            stack.push(val);
        }
        return stack;
    }
};

TEST_F(StackTest, PushPopTest) {
    Stack<int> stack(3);

    stack.push(10);
    stack.push(20);
    stack.push(30);

    EXPECT_EQ(stack.getSize(), 3);
    EXPECT_EQ(stack.top(), 30);

    stack.pop();
    EXPECT_EQ(stack.getSize(), 2);
    EXPECT_EQ(stack.top(), 20);

    stack.pop();
    EXPECT_EQ(stack.getSize(), 1);
    EXPECT_EQ(stack.top(), 10);

    stack.pop();
    EXPECT_EQ(stack.getSize(), 0);
    EXPECT_TRUE(stack.isEmpty());
}

TEST_F(StackTest, PushOverflowTest) {
    Stack<int> stack(2);

    stack.push(1);
    stack.push(2);

    EXPECT_THROW(stack.push(3), std::runtime_error);
    EXPECT_EQ(stack.getSize(), 2);
}

TEST_F(StackTest, PopEmptyTest) {
    Stack<int> stack(2);

    EXPECT_THROW(stack.pop(), std::runtime_error);
}

TEST_F(StackTest, TopEmptyTest) {
    Stack<int> stack(2);

    EXPECT_THROW(stack.top(), std::runtime_error);
}

TEST_F(StackTest, CopyConstructorTest) {
    Stack<int> originalStack = createStack(3, { 1, 2, 3 });

    Stack<int> copiedStack = originalStack;

    EXPECT_EQ(copiedStack.getSize(), 3);
    EXPECT_EQ(copiedStack.top(), 3);

    copiedStack.pop();
    EXPECT_EQ(copiedStack.top(), 2);
    EXPECT_EQ(originalStack.top(), 3); 
}

TEST_F(StackTest, MoveConstructorTest) {
    Stack<int> originalStack = createStack(3, { 1, 2, 3 });

    Stack<int> movedStack = std::move(originalStack);

    EXPECT_EQ(movedStack.getSize(), 3);
    EXPECT_EQ(movedStack.top(), 3);

    EXPECT_EQ(originalStack.getSize(), 0); 
    EXPECT_TRUE(originalStack.isEmpty());
}

TEST_F(StackTest, CopyAssignmentTest) {
    Stack<int> originalStack = createStack(3, { 10, 20, 30 });
    Stack<int> assignedStack(3); 

    assignedStack = originalStack;

    EXPECT_EQ(assignedStack.getSize(), 3);
    EXPECT_EQ(assignedStack.top(), 30);

    assignedStack.pop();
    EXPECT_EQ(assignedStack.top(), 20);
    EXPECT_EQ(originalStack.top(), 30);
}

TEST_F(StackTest, MoveAssignmentTest) {
    Stack<int> originalStack = createStack(3, { 100, 200, 300 });
    Stack<int> movedStack(3);

    movedStack = std::move(originalStack);

    EXPECT_EQ(movedStack.getSize(), 3);
    EXPECT_EQ(movedStack.top(), 300);

    EXPECT_EQ(originalStack.getSize(), 0);
    EXPECT_TRUE(originalStack.isEmpty());
}

TEST_F(StackTest, CapacityTest) {
    Stack<int> stack(5);

    EXPECT_EQ(stack.getCapacity(), 5);
    EXPECT_TRUE(stack.isEmpty());

    stack.push(10);
    EXPECT_EQ(stack.getSize(), 1);
    EXPECT_EQ(stack.getCapacity(), 5);

    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);

    EXPECT_EQ(stack.getSize(), 5);
    EXPECT_EQ(stack.getCapacity(), 5);
}

TEST_F(StackTest, OverflowExceptionTest) {
    Stack<int> stack(3);

    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_THROW(stack.push(4), std::runtime_error); 
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}