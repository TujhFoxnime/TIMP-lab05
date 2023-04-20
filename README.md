# TIMP-lab05


1) git clone https://github.com/tp-labs/lab05.git
2) git remote remove origin
3) git remote add origin https://github.com/TujhFoxnime/TIMP-lab05.git
4) mkdir gtests
5) cd gtests
6) nano Testfile.cpp  :


-#include <Account.h>
-#include <Transaction.h>
-#include <gtest/gtest.h>
-
-TEST(Banking, Account) {
-Account acc(0, 0);
-
-ASSERT_EQ(acc.GetBalance(), 0);
-ASSERT_THROW(acc.ChangeBalance(1234), std::runtime_error);
-acc.Lock();
-ASSERT_NO_THROW(acc.ChangeBalance(1234));
-ASSERT_THROW(acc.Lock(), std::runtime_error);
-ASSERT_EQ(acc.GetBalance(), 1234);
-acc.ChangeBalance(-1235);
-ASSERT_EQ(acc.GetBalance(), -1);
-acc.Unlock();
-ASSERT_THROW(acc.ChangeBalance(1234), std::runtime_error);
-}
-
-TEST(Banking, Transaction) {
-Account acc1(1, 1500);
-Account acc2(2, 1500);
-Transaction transaction;
-
-ASSERT_EQ(transaction.fee(), 1);
-transaction.set_fee(20);
-ASSERT_EQ(transaction.fee(), 20);
-
-ASSERT_THROW(transaction.Make(acc1, acc2, -345), std::invalid_argument);
-ASSERT_THROW(transaction.Make(acc2, acc2, 1000), std::logic_error);
-ASSERT_THROW(transaction.Make (acc1, acc2, 40), std::logic_error);
-transaction.set_fee(100);
-ASSERT_EQ(transaction.Make(acc1, acc2, 150), false);
-ASSERT_EQ(transaction.Make(acc1, acc2, 2000), false);
-
-ASSERT_EQ(transaction.Make(acc1, acc2, 1000), true);
-ASSERT_EQ(acc2.GetBalance(), 2500);
-ASSERT_EQ(acc1.GetBalance(), 400);
-}


7) cd ..
8) nano CMakeLists.txt    :


-cmake_minimum_required(VERSION 3.22.1 FATAL_ERROR)
-add_compile_options(--coverage)
-project(banking)
-
-add_library(banking_lib STATIC  ${CMAKE_CURRENT_SOURCE_DIR}/banking/Transaction.cpp 
                                ${CMAKE_CURRENT_SOURCE_DIR}/banking/Account.cpp)
-add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest gtest)
-add_executable(run_test ${CMAKE_CURRENT_SOURCE_DIR}/gtests/Testfile.cpp)
-
-target_include_directories(run_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/banking)
-target_compile_options(run_test PRIVATE --coverage)
-target_link_libraries(run_test PRIVATE --coverage)
-target_link_libraries(run_test PUBLIC banking_lib gtest_main)


9) mkdir .github/workflows
10) cd .github/workflows
11) nano CI.yml    :


*name: Running
*on:
* push:
*  branches: [main]
* pull_request:
*  branches: [main]
*
*jobs:
* build_Linux:
*  runs-on: ubuntu-latest
*  steps:
*  - uses: actions/checkout@v3
*
*  - name: Add GTest
*    run: git clone https://github.com/google/googletest.git third-party/gtest -b release-1.11.0
*
*  - name: Install lcov
*    run: sudo apt-get install -y lcov
*
*  - name: CMake banking and tests
*    run: cmake ${{github.workspace}} -B ${{github.workspace}}/build
*
*  - name: Build B&T
*    run: cmake --build ${{github.workspace}}/build
*
*  - name: Run test
*    run: ${{github.workspace}}/build/run_test
*
*  - name: Make Coverage Process
*    run: |
*      cd ${{github.workspace}}/build
*      lcov -t "Testfile Coverage" -o Testfile.info -c -d .
*  - name: Publish to coveralls.io
*    uses: coverallsapp/github-action@master
*    with:
*      github-token: ${{ secrets.GITHUB_TOKEN }}
*      parallel: true
*      path-to-lcov: ${{github.workspace}}/build/Testfile.info
*      coveralls-endpoint: https://coveralls.io
*
*  - name: End coveralls
*    uses: coverallsapp/github-action@master
*    with:
*      github-token: ${{ secrets.github_token }}
*      parallel-finished: true


12) cd ..
13) cd ..
14) git add -A
    git commit -m "..."
    git push origin HEAD:main

