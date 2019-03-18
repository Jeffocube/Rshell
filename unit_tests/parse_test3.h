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

TEST(parse_test3, RIGHT_TEST) {
    commandComp* comm = new commandComp();
    newParse("echo hello > text.txt", comm);
    EXPECT_EQ(comm->getActivity(1), ">");
}
TEST(parse_test3, LEFT_TEST) {
    commandComp* comm = new commandComp();
    newParse("echo hello  < text.txt", comm);
    EXPECT_EQ(comm->getActivity(1), "<");
}
TEST(parse_test3, PIPE_TEST) {
    commandComp* comm = new commandComp();
    newParse("ls | text.txt", comm);
    EXPECT_EQ(comm->getActivity(1), "|");
}
TEST(parse_test3, APPEND_TEST) {
    commandComp* comm = new commandComp();
    newParse("ls >> text.txt", comm);
    EXPECT_EQ(comm->getActivity(1), ">>");
}