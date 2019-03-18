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

TEST(D_C_TEST, RIGHT_TEST_TRUE) {
    commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("ls", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("t.txt", tstrVec);
    dummy->setPass(true, 1);
    testVec.push_back(dummy);
    Connector* RIGHT = new Connector(">", comm);
    testVec.push_back(RIGHT);
    testVec.push_back(dummy2);
    comm->setVec(testVec);
    EXPECT_EQ(RIGHT->execute(1), 2);
}
TEST(D_C_TEST, RIGHT_TEST_CHECK) {
    commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("ls", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("t.txt", tstrVec);
    dummy->setPass(true, 1);
    testVec.push_back(dummy);
    Connector* RIGHT = new Connector(">", comm);
    testVec.push_back(RIGHT);
    testVec.push_back(dummy2);
    comm->setVec(testVec);
    EXPECT_EQ(RIGHT->getActivity(1), ">");
}
TEST(D_C_TEST, APPEND_TEST_CHECK) {
    commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("ls", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("t.txt", tstrVec);
    dummy->setPass(true, 1);
    testVec.push_back(dummy);
    Connector* RIGHT = new Connector(">>", comm);
    testVec.push_back(RIGHT);
    testVec.push_back(dummy2);
    comm->setVec(testVec);
    EXPECT_EQ(RIGHT->getActivity(1), ">>");
}
TEST(D_C_TEST, APPEND_TEST_TRUE) {
    commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("ls", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("t.txt", tstrVec);
    dummy->setPass(true, 1);
    testVec.push_back(dummy);
    Connector* RIGHT = new Connector(">>", comm);
    testVec.push_back(RIGHT);
    testVec.push_back(dummy2);
    comm->setVec(testVec);
    EXPECT_EQ(comm->getInComm(0), true);
}
TEST(D_C_TEST, APPEND_TEST_TRUE2) {
    commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("ls", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("t.txt", tstrVec);
    dummy->setPass(true, 1);
    testVec.push_back(dummy);
    Connector* RIGHT = new Connector(">>", comm);
    testVec.push_back(RIGHT);
    testVec.push_back(dummy2);
    comm->setVec(testVec);
    RIGHT->execute(1);
    EXPECT_EQ(comm->getInComm(2), true);
}