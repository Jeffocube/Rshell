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

TEST(connector_test, AND_TEST_TRUE) {
    commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("dummy1", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("dummy2", tstrVec);
    dummy->setPass(true, 1);
    testVec.push_back(dummy);
    Connector* AND1 = new Connector("&&", comm);
    testVec.push_back(AND1);
    testVec.push_back(dummy2);
    comm->setVec(testVec);
    EXPECT_EQ(AND1->execute(1), 1);
}
TEST(connector_test, AND_TEST_FALSE) {
    commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("dummy1", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("dummy2", tstrVec);
    dummy->setPass(true, 1);
    testVec.push_back(dummy);
    Connector* AND1 = new Connector("&&", comm);
    testVec.push_back(AND1);
    testVec.push_back(dummy2);
    comm->setVec(testVec);
    dummy->setPass(false, 1);
    EXPECT_EQ(AND1->execute(1), 2);
}
TEST(connector_test, OR_TEST_TRUE) {
    commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("dummy1", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("dummy2", tstrVec);
    dummy->setPass(true, 1);
    testVec.push_back(dummy);
    Connector* AND1 = new Connector("||", comm);
    testVec.push_back(AND1);
    testVec.push_back(dummy2);
    comm->setVec(testVec);
    EXPECT_EQ(AND1->execute(1), 2);
}
TEST(connector_test, OR_TEST_FALSE) {
    commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("dummy1", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("dummy2", tstrVec);
    dummy->setPass(true, 1);
    testVec.push_back(dummy);
    Connector* AND1 = new Connector("||", comm);
    testVec.push_back(AND1);
    testVec.push_back(dummy2);
    comm->setVec(testVec);
    dummy->setPass(false, 1);
    EXPECT_EQ(AND1->execute(1), 1);
}
TEST(connector_test, SEMI_TEST_TRUE) {
    commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("dummy1", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("dummy2", tstrVec);
    dummy->setPass(true, 1);
    testVec.push_back(dummy);
    Connector* AND1 = new Connector(";", comm);
    testVec.push_back(AND1);
    testVec.push_back(dummy2);
    comm->setVec(testVec);
    EXPECT_EQ(AND1->execute(1), 1);
}
TEST(connector_test, SEMI_TEST_FALSE) {
    commandComp* comm = new commandComp();
    vector<Input* > testVec;
    vector<string > tstrVec;
    commandLeaf* dummy = new commandLeaf("dummy1", tstrVec);
    commandLeaf* dummy2 = new commandLeaf("dummy2", tstrVec);
    dummy->setPass(true, 1);
    testVec.push_back(dummy);
    Connector* AND1 = new Connector(";", comm);
    testVec.push_back(AND1);
    testVec.push_back(dummy2);
    comm->setVec(testVec);
    dummy->setPass(false, 1);
    EXPECT_EQ(AND1->execute(1), 1);    
}
    
    
    