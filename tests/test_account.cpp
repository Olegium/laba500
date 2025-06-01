#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"

using ::testing::Return;
using ::testing::_;

TEST(AccountTest, ConstructorAndGetBalance) {
    Account account(1, 100);
    EXPECT_EQ(account.getBalance(), 100);
    EXPECT_EQ(account.getId(), 1);
}

TEST(AccountTest, ChangeBalanceSuccess) {
    Account account(1, 100);
    account.lock();
    account.changeBalance(50);
    EXPECT_EQ(account.getBalance(), 150);
    account.unlock();
}

TEST(AccountTest, ChangeBalanceNotLocked) {
    Account account(1, 100);
    EXPECT_THROW(account.changeBalance(50), std::runtime_error);
    EXPECT_EQ(account.getBalance(), 100);
}

TEST(AccountTest, LockUnlock) {
    Account account(1, 100);
    account.lock();
    EXPECT_THROW(account.lock(), std::runtime_error);
    account.unlock();
    EXPECT_NO_THROW(account.unlock());
}