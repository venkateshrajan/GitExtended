#include "pch.h"
#include <gtest/gtest.h>

#include "git_wrapper.h"

class CommandGitFixture : public gitex::CGitCommand, public testing::Test {
public:
  CommandGitFixture() : gitex::CGitCommand("git") {}
};


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


#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include "utilities.h"

TEST(Utilites, launch_process_test) {
  std::string output;
  int ret = gitex::launch_process("git", {"--version"}, output);

  ASSERT_EQ(ret, 0);
  ASSERT_TRUE(!output.empty());
  std::string expected_prefix = "git version";
  ASSERT_TRUE(!output.compare(0, expected_prefix.size(), expected_prefix));
}

TEST(Utilites, launch_process_multilineoutput_test) {
  std::string output;
  int ret = gitex::launch_process("zsh", {"-c", "echo hello && echo world"}, output);

  ASSERT_EQ(ret, 0);
  ASSERT_TRUE(!output.empty());

  std::vector<std::string> lines;
  boost::split(lines, output, boost::is_any_of("\n"));
  ASSERT_TRUE(!lines[0].compare("hello"));
  ASSERT_TRUE(!lines[1].compare("world"));
}

TEST(Utilites, launch_process_error_test) {
  std::string output;
  std::string error;
  int ret = gitex::launch_process("git", {"hello"}, output, error);

  ASSERT_EQ(ret, 1);
  ASSERT_TRUE(output.empty());
  ASSERT_FALSE(error.empty());
}

int main (int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
