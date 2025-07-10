#include <string>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "SimpleCalculator.h"
#include "IHistory.h"

namespace calc {
    class MockHistory : public IHistory {
    public:
        MOCK_METHOD(void, AddEntry, (const std::string&), (override));
        MOCK_METHOD(std::vector<std::string>, GetLastOperations, (size_t), (const override));
    };

    class SimpleCalculatorTest : public ::testing::Test {
    protected:
        MockHistory mockHistory;
        SimpleCalculator calculator{mockHistory};
    };

    // Проверка сложения
    TEST_F(SimpleCalculatorTest, Add_TwoNumbers_CorrectResultAndLogsToHistory) {
        struct AddTestCase {
            int left, right;
            int expected;
            std::string expected_log;
        };

        std::vector<AddTestCase> const test_cases = {
            {2, 2, 4, "2 + 2 = 4"},
            {0, 0, 0, "0 + 0 = 0"},
            {1, -1, 0, "1 + -1 = 0"},
            {-2, -2, -4, "-2 + -2 = -4"},
            {2, -1, 1, "2 + -1 = 1"},
            {-2, 1, -1, "-2 + 1 = -1"},
        };

        for (auto const &test_case: test_cases) {
            EXPECT_CALL(mockHistory, AddEntry(test_case.expected_log)).Times(1);
            EXPECT_EQ(calculator.Add(test_case.left, test_case.right), test_case.expected);
        }
    }

    // Проверка вычитания
    TEST_F(SimpleCalculatorTest, Subtract_TwoNumbers_CorrectResultAndLogsToHistory) {
        struct SubtractTestCase {
            int left, right;
            int expected;
            std::string expected_log;
        };

        std::vector<SubtractTestCase> const test_cases = {
            {2, 2, 0, "2 - 2 = 0"},
            {0, 0, 0, "0 - 0 = 0"},
            {1, -1, 2, "1 - -1 = 2"},
            {-2, -2, 0, "-2 - -2 = 0"},
            {2, -1, 3, "2 - -1 = 3"},
            {-2, 1, -3, "-2 - 1 = -3"},
        };

        for (auto const &test_case: test_cases) {
            EXPECT_CALL(mockHistory, AddEntry(test_case.expected_log)).Times(1);
            EXPECT_EQ(calculator.Subtract(test_case.left, test_case.right), test_case.expected);
        }
    }

    // Проверка умножения
    TEST_F(SimpleCalculatorTest, Multiply_TwoNumbers_CorrectResultAndLogsToHistory) {
        struct MultiplyTestCase {
            int left, right;
            int expected;
            std::string expected_log;
        };

        std::vector<MultiplyTestCase> const test_cases = {
            {2, 2, 4, "2 * 2 = 4"},
            {0, 0, 0, "0 * 0 = 0"},
            {1, -1, -1, "1 * -1 = -1"},
            {-2, -2, 4, "-2 * -2 = 4"},
            {2, 0, 0, "2 * 0 = 0"},
            {-2, 0, 0, "-2 * 0 = 0"},
        };

        for (auto const &test_case: test_cases) {
            EXPECT_CALL(mockHistory, AddEntry(test_case.expected_log)).Times(1);
            EXPECT_EQ(calculator.Multiply(test_case.left, test_case.right), test_case.expected);
        }
    }

    // Проверка деления
    TEST_F(SimpleCalculatorTest, Divide_TwoNumbers_CorrectResultAndLogsToHistory) {
        struct DivideTestCase {
            int left, right;
            int expected;
            std::string expected_log;
        };

        std::vector<DivideTestCase> const test_cases = {
            {2, 2, 1, "2 / 2 = 1"},
            {2, -2, -1, "2 / -2 = -1"},
            {3, 2, 1, "3 / 2 = 1"},
            {2, 3, 0, "2 / 3 = 0"},
        };

        for (auto const &test_case: test_cases) {
            EXPECT_CALL(mockHistory, AddEntry(test_case.expected_log)).Times(1);
            EXPECT_EQ(calculator.Divide(test_case.left, test_case.right), test_case.expected);
        }
    }

    // Проверка деления на ноль
    TEST_F(SimpleCalculatorTest, Divide_ByZero_ThrowsException_NotSignal) {
        EXPECT_CALL(mockHistory, AddEntry).Times(0);
        EXPECT_THROW(calculator.Divide(1, 0), std::invalid_argument);
    }
} // namespace calc
