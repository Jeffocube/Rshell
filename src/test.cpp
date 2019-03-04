#include <iostream>
#include <vector>
#include <unistd.h>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "header/input.h"
#include "header/command.h"
#include "header/connector.h"
#include "header/exit.h"
#include "header/newParse.h"
#include "gtest/gtest.h"
#include "../unit_tests/connector_test.h"
#include "../unit_tests/leaf_test.h"
#include "../unit_tests/parse_test.h"
#include "../unit_tests/parse_test2.h"
#include "../unit_tests/test_test.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}