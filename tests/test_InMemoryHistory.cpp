#include <string>

#include <gtest/gtest.h>

#include "InMemoryHistory.h"

namespace calc {
    class InMemoryHistoryTest : public ::testing::Test {
    protected:
        InMemoryHistory history;
    };

    // Проверка добавления операции
    TEST_F(InMemoryHistoryTest, AddEntry_OperationIsStored) {
        std::vector<std::string> const entries = {
            "1 + 1 = 2",
            "1 - 1 = 0",
            "1 * 1 = 1",
            "1 / 1 = 1",
        };

        for (auto const& entry : entries) {
            history.AddEntry(entry);
        }

        auto last_ops = history.GetLastOperations(entries.size());

        ASSERT_EQ(last_ops.size(), entries.size());

        for (std::size_t i = 0; i < last_ops.size(); ++i) {
            EXPECT_EQ(last_ops[i], entries[i]);
        }
    }

    // Проверка получения последних N операций
    TEST_F(InMemoryHistoryTest, GetLastOperations_ReturnsCorrectSubset) {
        std::vector<std::string> const entries = {
            "1 + 1 = 2",
            "1 - 1 = 0",
            "1 * 1 = 1",
            "1 / 1 = 1",
        };
        std::size_t const last_op_cnt = 3;

        for (auto const& entry : entries) {
            history.AddEntry(entry);
        }

        auto last_ops = history.GetLastOperations(last_op_cnt);
        ASSERT_EQ(last_ops.size(), last_op_cnt);

        for (std::size_t i = 0; i < last_ops.size(); ++i) {
            EXPECT_EQ(last_ops[i], entries[entries.size() - last_op_cnt + i]);
        }

        auto all_ops = history.GetLastOperations(entries.size() * 2);
        ASSERT_EQ(all_ops.size(), entries.size());
    }

} // namespace calc