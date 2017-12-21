#include "RuleSet.h"

#include <gtest/gtest.h>

TEST(RuleSet, UnderPopulation) {
    RuleSet ruleSet;
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 0));
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 1));
}

TEST(RuleSet, StayAlive) {
    RuleSet ruleSet;
    EXPECT_EQ(alive, ruleSet.evaluateNewState(alive, 2));
    EXPECT_EQ(alive, ruleSet.evaluateNewState(alive, 3));
}

TEST(RuleSet, OverPopulation) {
    RuleSet ruleSet;
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 4));
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 5));
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 6));
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 7));
    EXPECT_EQ(dead, ruleSet.evaluateNewState(alive, 8));
}

TEST(RuleSet, Reproduction) {
    RuleSet ruleSet;
    EXPECT_EQ(alive, ruleSet.evaluateNewState(dead, 3));
}
