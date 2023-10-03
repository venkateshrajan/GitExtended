#include "pch.h"
#include <gtest/gtest.h>

#include "git_wrapper.h"

class CommandGitFixture : public gitex::CGitCommand, public testing::Test {
public:
  CommandGitFixture() : gitex::CGitCommand("git") {}
protected:
  template<typename... Args>
  int runCommand(std::vector<std::string>& output,
                 std::vector<std::string>& error,
                 Args... args) {
    return gitex::CGitCommand::runCommand(output, error, args...);
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


TEST_F(CommandGitFixture, parse_status_success_test) {
  std::vector<std::string> input = {
    "M\tgitex/src/Main.cpp",
    "C\tlibgitex/inc/GitExtended.h",
    "R\tlibgitex/inc/git_wrapper.h",
    "A\tlibgitex/inc/utilities.h",
    "D\tlibgitex/src/CMakeLists.txt",
    "U\tlibgitex/src/GitExtended.cpp"
  };

  gitex::FileStatusMap statuses;
  ASSERT_TRUE(parse_status(input, statuses));

  ASSERT_EQ(0, statuses["gitex/src/Main.cpp"]);
  ASSERT_EQ(1, statuses["libgitex/inc/GitExtended.h"]);
  ASSERT_EQ(2, statuses["libgitex/inc/git_wrapper.h"]);
  ASSERT_EQ(3, statuses["libgitex/inc/utilities.h"]);
  ASSERT_EQ(4, statuses["libgitex/src/CMakeLists.txt"]);
  ASSERT_EQ(5, statuses["libgitex/src/GitExtended.cpp"]);
}


TEST_F(CommandGitFixture, parse_status_failure_test1) {
  std::vector<std::string> input = {
    "X\tgitex/src/Main.cpp",
  };

  gitex::FileStatusMap statuses;
  ASSERT_FALSE(parse_status(input, statuses));
}


TEST_F(CommandGitFixture, parse_status_failure_test2) {
  std::vector<std::string> input = {
    "X\tgitex/src/Main.cpp\thello",
  };

  gitex::FileStatusMap statuses;
  ASSERT_FALSE(parse_status(input, statuses));
}

int main (int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
