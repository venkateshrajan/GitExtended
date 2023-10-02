#include "pch.h"
#include <gtest/gtest.h>

#include "git_wrapper.h"

class CommandGitFixture : public gitex::CCommandGitOp, public testing::Test {
public:
  CommandGitFixture() : gitex::CCommandGitOp("git") {}
protected:
  template<typename... Args>
  int runCommand(std::vector<std::string>& output,
                 std::vector<std::string>& error,
                 Args... args) {
    return gitex::CCommandGitOp::runCommand(output, error, args...);
  }
};

TEST_F(CommandGitFixture, runCommandTest) {
  std::vector<std::string> output;
  std::vector<std::string> error;
  int ret = runCommand(output, error, "--version");

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
