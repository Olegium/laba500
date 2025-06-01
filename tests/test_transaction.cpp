#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Transaction.h"

using ::testing::Return;
using ::testing::_;

class MockAccount {
public:
    MOCK_METHOD(int, getBalance, (), (const));
    MOCK_METHOD(int, getId, (), (const));
    MOCK_METHOD(void, changeBalance, (int diff));
    MOCK_METHOD(void, lock, ());
    MOCK_METHOD(void, unlock, ());
};

TEST(TransactionTest, MakeSuccess) {
    MockAccount from, to;
    EXPECT_CALL(from, getBalance()).WillOnce(Return(150));
    EXPECT_CALL(from, lock());
    EXPECT_CALL(from, changeBalance(-100));
    EXPECT_CALL(from, unlock());
    EXPECT_CALL(to, lock());
    EXPECT_CALL(to, changeBalance(100));
    EXPECT_CALL(to, unlock());
    Transaction transaction;
    EXPECT_TRUE(transaction.make(from, to, 100));
}

TEST(TransactionTest, MakeNegativeAmount) {
    MockAccount from, to;
    Transaction transaction;
    EXPECT_THROW(transaction.make(from, to, -100), std::invalid_argument);
}

TEST(TransactionTest, MakeInsufficientFunds) {
    MockAccount from, to;
    EXPECT_CALL(from, getBalance()).WillOnce(Return(50));
    EXPECT_CALL(from, lock());
    EXPECT_CALL(from, unlock());
    EXPECT_CALL(to, lock());
    EXPECT_CALL(to, unlock());
    Transaction transaction;
    EXPECT_FALSE(transaction.make(from, to, 100));
}

TEST(TransactionTest, CreditSuccess) {
    MockAccount account;
    EXPECT_CALL(account, lock());
    EXPECT_CALL(account, changeBalance(100));
    EXPECT_CALL(account, unlock());
    Transaction::credit(account, 100);
}

TEST(TransactionTest, DebitSuccess) {
    MockAccount account;
    EXPECT_CALL(account, getBalance()).WillOnce(Return(200));
    EXPECT_CALL(account, lock());
    EXPECT_CALL(account, changeBalance(-100));
    EXPECT_CALL(account, unlock());
    EXPECT_TRUE(Transaction::debit(account, 100));
}

TEST(TransactionTest, DebitInsufficientFunds) {
    MockAccount account;
    EXPECT_CALL(account, getBalance()).WillOnce(Return(50));
    EXPECT_CALL(account, lock());
    EXPECT_CALL(account, unlock());
    EXPECT_FALSE(Transaction::debit(account, 100));
}

TEST(TransactionTest, SaveToDatabase) {
    MockAccount from, to;
    EXPECT_CALL(from, getId()).WillOnce(Return(1));
    EXPECT_CALL(to, getId()).WillOnce(Return(2));
    EXPECT_CALL(from, getBalance()).WillOnce(Return(50));
    EXPECT_CALL(to, getBalance()).WillOnce(Return(150));
    testing::internal::CaptureStdout();
    Transaction::saveToDatabase(from, to, 100);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("from.id() == 1 is from.getBalance() == 50") != std::string::npos);
}