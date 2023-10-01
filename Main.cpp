#include "pch.h"

#include "absl/strings/str_join.h"
#include "GitExtended.h"
#include "utilities.h"

int main() {
  CGitExtended git;
  git.sayHello();

  std::vector<std::string> v = {"foo", "bar", "baz"};
  std::string s = absl::StrJoin(v, "-");

  std::cout << "Joined string: " << s << std:: endl;
  
  return 0;
}

