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

TEST(parse_test2, E_TEST) {
    commandComp* comm = new commandComp();
    newParse("[ -e hello ]", comm);
    EXPECT_EQ(comm->getActivity(0), "-e");
}
TEST(parse_test2, D_TEST) {
    commandComp* comm = new commandComp();
    newParse("[ -d hello ]", comm);
    EXPECT_EQ(comm->getActivity(0), "-d");
}
TEST(parse_test2, F_TEST) {
    commandComp* comm = new commandComp();
    newParse("[ -f hello ]", comm);
    EXPECT_EQ(comm->getActivity(0), "-f");
}
TEST(parse_test2, E_TEST1) {
    commandComp* comm = new commandComp();
    newParse("test -e hello", comm);
    EXPECT_EQ(comm->getActivity(0), "-e");
}
TEST(parse_test2, D_TEST2) {
    commandComp* comm = new commandComp();
    newParse("test -d hello", comm);
    EXPECT_EQ(comm->getActivity(0), "-d");
}
TEST(parse_test2, F_TEST3) {
    commandComp* comm = new commandComp();
    newParse("test -f hello", comm);
    EXPECT_EQ(comm->getActivity(0), "-f");
}