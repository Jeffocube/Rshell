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
TEST(leaf_test, AND_TEST) {
commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("echo", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("dummy2", tstrVec);
    testVec.push_back(dummy);
    Connector* AND1 = new Connector("&&", comm);
    testVec.push_back(AND1);
    testVec.push_back(dummy2);
    comm->setVec(testVec);
    comm->execute(1);
    EXPECT_EQ(dummy->getPass(), true);
}
TEST(leaf_test, AND_OR_TEST) {
commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("echo", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("dummy2", tstrVec);
    commandLeaf* dummy3 = new commandLeaf("dummy3", tstrVec);
    testVec.push_back(dummy);
    Connector* AND1 = new Connector("&&", comm);
    Connector* OR1 = new Connector("||", comm);
    testVec.push_back(AND1);
    testVec.push_back(dummy2);
    testVec.push_back(OR1);
    testVec.push_back(dummy3);
    comm->setVec(testVec);
    comm->execute(1);
    EXPECT_EQ(dummy2->getPass(), false);
    EXPECT_EQ(dummy3->getPass(), false);
}
TEST(leaf_test, OR_OR_TEST) {
commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("echo", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("dummy2", tstrVec);
    commandLeaf* dummy3 = new commandLeaf("dummy3", tstrVec);
    testVec.push_back(dummy);
    Connector* AND1 = new Connector("||", comm);
    Connector* OR1 = new Connector("||", comm);
    testVec.push_back(AND1);
    testVec.push_back(dummy2);
    testVec.push_back(OR1);
    testVec.push_back(dummy3);
    comm->setVec(testVec);
    comm->execute(1);
    EXPECT_EQ(dummy2->getPass(), true);
    EXPECT_EQ(dummy3->getPass(), true);
}

