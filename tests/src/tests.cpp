#include "pch.h"
#include <gtest/gtest.h>

#include "git_wrapper.h"

class CommandGitFixture : public gitex::CCommandGitOp, public testing::Test {
public:
  CommandGitFixture() : gitex::CCommandGitOp("git") {}
};

TEST_F(CommandGitFixture, runCommandTest) {
  std::vector<std::string> output;
  std::vector<std::string> error;
  int ret = runCommand("--version", output, error);

  ASSERT_EQ(ret, 0);
  ASSERT_EQ(output.size(), 1);
  ASSERT_TRUE(error.empty());
  std::string expected_prefix = "git version";
  ASSERT_TRUE(!output[0].compare(0, expected_prefix.size(), expected_prefix));
}

int main (int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
