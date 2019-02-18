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

TEST(leaf_test, NO_RUN_TRUE_TEST) {
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("dummy1", tstrVec);
    dummy->setPass(true, 1);
    EXPECT_EQ(dummy->getPass(), true);
}
TEST(leaf_test, NO_RUN_FALSE_TEST) {
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("dummy1", tstrVec);
    EXPECT_EQ(dummy->getPass(), false);
}
TEST(leaf_test, RUN_FALSE_TEST) {
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("dummy1", tstrVec);
    dummy->execute(1);
    EXPECT_EQ(dummy->getPass(), false);
}
TEST(leaf_test, RUN_TRUE_TEST) {
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("echo", tstrVec);
    dummy->setPass(true, 1);
    dummy->execute(1);
    EXPECT_EQ(dummy->getPass(), true);
}


