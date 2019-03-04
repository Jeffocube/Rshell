#include <iostream>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "../src/header/input.h"
#include "../src/header/command.h"
#include "../src/header/connector.h"
#include "../src/header/exit.h"
#include "../src/header/newParse.h"
#include "../src/header/tester.h"
#include "gtest/gtest.h"

TEST(test_test, TRUE_TEST1) {
    commandComp* comm = new commandComp();
    newParse("[ -f CMakeLists.txt ]", comm);
    int i;
    comm->execute(i);
    EXPECT_EQ(comm->getPass(), true);
}
TEST(test_test, TRUE_TEST2) {
    commandComp* comm = new commandComp();
    newParse("[ -e CMakeLists.txt ]", comm);
    int i;
    comm->execute(i);
    EXPECT_EQ(comm->getPass(), true);
}
TEST(test_test, TRUE_TEST3) {
    commandComp* comm = new commandComp();
    newParse("[ -d src ]", comm);
    int i;
    comm->execute(i);
    EXPECT_EQ(comm->getPass(), true);
}
TEST(test_test, TRUE_TEST4) {
    commandComp* comm = new commandComp();
    newParse("test -e CMakeLists.txt", comm);
    int i;
    comm->execute(i);
    EXPECT_EQ(comm->getPass(), true);
}
TEST(test_test, TRUE_TEST5) {
    commandComp* comm = new commandComp();
    newParse("test -d src", comm);
    int i;
    comm->execute(i);
    EXPECT_EQ(comm->getPass(), true);
}
TEST(test_test, TRUE_TEST6) {
    commandComp* comm = new commandComp();
    newParse("test -f CMakeLists.txt", comm);
    int i;
    comm->execute(i);
    EXPECT_EQ(comm->getPass(), true);
}
TEST(test_test, FALSE_TEST1) {
    commandComp* comm = new commandComp();
    newParse("[ -e hello ]", comm);
    int i;
    comm->execute(i);
    EXPECT_EQ(comm->getPass(), false);
}
TEST(test_test, FALSE_TEST2) {
    commandComp* comm = new commandComp();
    newParse("[ -d hello ]", comm);
    int i;
    comm->execute(i);
    EXPECT_EQ(comm->getPass(), false);
}
TEST(test_test, FALSE_TEST3) {
    commandComp* comm = new commandComp();
    newParse("[ -f hello ]", comm);
    int i;
    comm->execute(i);
    EXPECT_EQ(comm->getPass(), false);
}
TEST(test_test, FALSE_TEST4) {
    commandComp* comm = new commandComp();
    newParse("test -e hello", comm);
    int i;
    comm->execute(i);
    EXPECT_EQ(comm->getPass(), false);
}
TEST(test_test, FALSE_TEST5) {
    commandComp* comm = new commandComp();
    newParse("test -d hello", comm);
    int i;
    comm->execute(i);
    EXPECT_EQ(comm->getPass(), false);
}
TEST(test_test, FALSE_TEST6) {
    commandComp* comm = new commandComp();
    newParse("test -f hello", comm);
    int i;
    comm->execute(i);
    EXPECT_EQ(comm->getPass(), false);
}