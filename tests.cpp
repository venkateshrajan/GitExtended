#include "pch.h"
#include <gtest/gtest.h>

#include "utilities.h"

TEST(UtilitiesTest, executeCommandReadsOutputCorrectly) {
  std::vector<std::string> output;
  int ret = util::executeCommand("echo hello && echo world", output);

  EXPECT_EQ(ret, 0);
  EXPECT_EQ(output.size(), 2);
  // executeCommand doesn't expect toe trim the strings 
  // that's the job of the caller
  EXPECT_STREQ(output[0].c_str(), "hello\n");
  EXPECT_STREQ(output[1].c_str(), "world\n");
}

TEST(UtilitiesTest, ltrim) {
  // single blank space
  std::string s1(" s1");
  util::ltrim(s1);
  EXPECT_STREQ(s1.c_str(), "s1");

  // multiple blank space
  std::string s2(" \t\n\rs2");
  util::ltrim(s2);
  EXPECT_STREQ(s2.c_str(), "s2");

  // only blank space
  std::string s3(" \t\n\r");
  util::ltrim(s3);
  EXPECT_STREQ(s3.c_str(), "");

  // no blank space
  std::string s4("s4");
  util::ltrim(s4);
  EXPECT_STREQ(s4.c_str(), "s4");
}

TEST(UtilitiesTest, rtrim) {
  // single blank space
  std::string s1("s1 ");
  util::rtrim(s1);
  EXPECT_STREQ(s1.c_str(), "s1");

  // multiple blank space
  std::string s2("s2 \t\n\r");
  util::rtrim(s2);
  EXPECT_STREQ(s2.c_str(), "s2");

  // only blank space
  std::string s3(" \t\n\r");
  util::rtrim(s3);
  EXPECT_STREQ(s3.c_str(), "");

  // no blank space
  std::string s4("s4");
  util::rtrim(s4);
  EXPECT_STREQ(s4.c_str(), "s4");
}

TEST(UtilitiesTest, trim) {
  // single blank space
  std::string s1(" s1 ");
  util::trim(s1);
  EXPECT_STREQ(s1.c_str(), "s1");

  // multiple blank space
  std::string s2(" \t\n\rs2 \t\n\r");
  util::trim(s2);
  EXPECT_STREQ(s2.c_str(), "s2");

  // only blank space
  std::string s3(" \t\n\r");
  util::trim(s3);
  EXPECT_STREQ(s3.c_str(), "");

  // no blank space
  std::string s4("s4");
  util::trim(s4);
  EXPECT_STREQ(s4.c_str(), "s4");
}

int main (int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
