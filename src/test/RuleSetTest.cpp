#include "RuleSet.h"

#include "gtest/gtest.h"

RuleSet ruleSet;

TEST(RuleSet, UnderPopulation) {
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 0));
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 1));
}

TEST(RuleSet, StayAlive) {
    EXPECT_EQ(alive, ruleSet.evaluateNewState(alive, 2));
    EXPECT_EQ(alive, ruleSet.evaluateNewState(alive, 3));
}

TEST(RuleSet, OverPopulation) {
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 4));
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 5));
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 6));
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 7));
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 8));
}

TEST(RuleSet, Reproduction) {
    EXPECT_EQ(alive, ruleSet.evaluateNewState(dead, 3));
}
