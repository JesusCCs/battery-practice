#include <gtest/gtest.h>
#include "../include/console.h"

class ConsoleTest : public ::testing::Test {

};


TEST_F(ConsoleTest, TestAskForFloatPositiveOnly) {
    auto testInput = new std::istringstream("-1\n-2.5\n5.4\n-27");

    auto console = new Console(testInput);

    EXPECT_FLOAT_EQ(console->askForFloat("", true), 5.4);
}

TEST_F(ConsoleTest, TestAskForFloatAnyNumber) {
    auto testInput = new std::istringstream("-1\n-2.5\n5.4\n-27");

    auto console = new Console(testInput);

    EXPECT_FLOAT_EQ(console->askForFloat(""), -1);
}

TEST_F(ConsoleTest, TestAskForFloatOnlyAcceptNumbers) {
    auto testInput = new std::istringstream("a\nb\nc\n-27");

    auto console = new Console(testInput);

    EXPECT_FLOAT_EQ(console->askForFloat(""), -27);
}


TEST_F(ConsoleTest, TestAskForIntegersAcceptsOnlyIntegers) {
    auto testInput = new std::istringstream("3.1416\n2.718\n1.618\n5");

    auto console = new Console(testInput);

    EXPECT_EQ(console->askForInteger("", 100, -100), 5);
}

TEST_F(ConsoleTest, TestAskForIntegersAcceptsOnlyNumbers) {
    auto testInput = new std::istringstream("a\nb\nc\n7");

    auto console = new Console(testInput);

    EXPECT_EQ(console->askForInteger("", 100, -100), 7);
}

TEST_F(ConsoleTest, TestAskForIntegersMaxValue) {
    auto testInput = new std::istringstream("12\n15\n18\n10");

    auto console = new Console(testInput);

    EXPECT_EQ(console->askForInteger("", 10, -100), 10);
}

TEST_F(ConsoleTest, TestAskForIntegersMinValue) {
    auto testInput = new std::istringstream("2\n1\n0\n3");

    auto console = new Console(testInput);

    EXPECT_EQ(console->askForInteger("", 100, 3), 3);
}