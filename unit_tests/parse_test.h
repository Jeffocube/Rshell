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
#include "gtest/gtest.h"

TEST(parse_test, SINGLE_TEST) {
    commandComp* comm = new commandComp();
    newParse("echo hello", comm);
    EXPECT_EQ(comm->getActivity(0), "echo");
}
TEST(parse_test, SEMI_TEST) {
    commandComp* comm = new commandComp();
    newParse("echo hello; echo hi", comm);
    EXPECT_EQ(comm->getActivity(0), "echo");
    EXPECT_EQ(comm->getActivity(1), ";");
    EXPECT_EQ(comm->getActivity(2), "echo");
}
TEST(parse_test, AND_TEST) {
    commandComp* comm = new commandComp();
    newParse("echo hello && echo hi", comm);
    EXPECT_EQ(comm->getActivity(0), "echo");
    EXPECT_EQ(comm->getActivity(1), "&&");
    EXPECT_EQ(comm->getActivity(2), "echo");
}
TEST(parse_test, OR_TEST_TRUE) {
    commandComp* comm = new commandComp();
    newParse("echo hello || echo hi", comm);
    EXPECT_EQ(comm->getActivity(0), "echo");
    EXPECT_EQ(comm->getActivity(1), "||");
    EXPECT_EQ(comm->getActivity(2), "echo");
}
TEST(parse_test, DIR_TEST) {
    commandComp* comm = new commandComp();
    newParse("dir; echo hello", comm);
    EXPECT_EQ(comm->getActivity(0), "dir");
    EXPECT_EQ(comm->getActivity(1), ";");
    EXPECT_EQ(comm->getActivity(2), "echo");
}
TEST(parse_test, SINGLE_DIR_TEST) {
    commandComp* comm = new commandComp();
    newParse("dir; echo hello", comm);
    EXPECT_EQ(comm->getActivity(0), "dir");
}
TEST(parse_test, QUOTES_TEST) {
    commandComp* comm = new commandComp();
    newParse("echo \"hello\" && echo hi", comm);
    EXPECT_EQ(comm->getActivity(2), "echo");
}