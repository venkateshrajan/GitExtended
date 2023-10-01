#include "pch.h"
#include <gtest/gtest.h>

#include "utilities.h"

TEST(UtilitiesTest, executeCommandReadsOutputCorrectly) {
  std::vector<std::string> output;
  int ret = util::executeCommand("printf 'hello\\nworld'", output);

  EXPECT_EQ(ret, 0);
  EXPECT_EQ(output.size(), 2);
  EXPECT_STREQ(output[0].c_str(), "hello");
  EXPECT_STREQ(output[1].c_str(), "world");
}

int main (int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
