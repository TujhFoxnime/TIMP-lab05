#include <Account.h>
#include <Transaction.h>
#include <gtest/gtest.h>

TEST(Banking, Account) {
Account acc(0, 0);

ASSERT_EQ(acc.GetBalance(), 0);
ASSERT_THROW(acc.ChangeBalance(1234), std::runtime_error);
acc.Lock();
ASSERT_NO_THROW(acc.ChangeBalance(1234));
ASSERT_THROW(acc.Lock(), std::runtime_error);
ASSERT_EQ(acc.GetBalance(), 1234);
acc.ChangeBalance(-1235);
ASSERT_EQ(acc.GetBalance(), -1);
acc.Unlock();
ASSERT_THROW(acc.ChangeBalance(1234), std::runtime_error);
}

TEST(Banking, Transaction) {
Account acc1(1, 1500);
Account acc2(2, 1500);
Transaction transaction;

ASSERT_EQ(transaction.fee(), 1);
transaction.set_fee(20);
ASSERT_EQ(transaction.fee(), 20);

ASSERT_THROW(transaction.Make(acc1, acc2, -345), std::invalid_argument);
ASSERT_THROW(transaction.Make(acc2, acc2, 1000), std::logic_error);
ASSERT_THROW(transaction.Make (acc1, acc2, 40), std::logic_error);
transaction.set_fee(100);
ASSERT_EQ(transaction.Make(acc1, acc2, 150), false);
ASSERT_EQ(transaction.Make(acc1, acc2, 2000), false);

ASSERT_EQ(transaction.Make(acc1, acc2, 1000), true);
ASSERT_EQ(acc2.GetBalance(), 2500);
ASSERT_EQ(acc1.GetBalance(), 400);
}
