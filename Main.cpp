#include "pch.h"

#include "absl/strings/str_join.h"
#include "GitExtended.h"
#include <linux/limits.h>

int main() {
  CGitExtended git;
  git.sayHello();

  std::vector<std::string> v = {"foo", "bar", "baz"};
  std::string s = absl::StrJoin(v, "-");

  std::cout << "Joined string: " << s << std:: endl;
  
  std::FILE *fp = popen("ls", "r");
  if (fp == NULL)
    return 1;

  char path[PATH_MAX] = { 0 };
  while (fgets(path, PATH_MAX, fp) != NULL)
    std::cout << path;

  return 0;
}

