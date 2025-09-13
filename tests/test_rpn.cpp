#include "gtest/gtest.h"
#include "../include/rpn.h"

TEST(RPNTest, BasicAddition) {
    EXPECT_EQ(evaluate_rpn("2 3 +"), 5);
}

TEST(RPNTest, BasicSubtraction) {
    EXPECT_EQ(evaluate_rpn("5 1 -"), 4);
}

TEST(RPNTest, Multiplication) {
    EXPECT_EQ(evaluate_rpn("3 4 *"), 12);
}

TEST(RPNTest, Division) {
    EXPECT_EQ(evaluate_rpn("10 2 /"), 5);
}

TEST(RPNTest, InvalidExpression) {
    EXPECT_THROW(evaluate_rpn("2 +"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("+"), std::invalid_argument);
    EXPECT_THROW(evaluate_rpn("2 0 /"), std::invalid_argument);
}
