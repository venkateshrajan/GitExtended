#include "pch.h"

#include "absl/strings/str_join.h"
#include "boost/process.hpp"
#include "GitExtended.h"
#include "utilities.h"

using namespace boost::process;

int main() {
  CGitExtended git;
  git.sayHello();

  std::vector<std::string> v = {"foo", "bar", "baz"};
  std::string s = absl::StrJoin(v, "-");

  std::cout << "Joined string: " << s << std:: endl;

  ipstream pipe_stream;
  child c("gcc --version", std_out > pipe_stream);

  std::string line;
  while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
    std::cerr << line << std::endl;
  
  c.wait();

  return 0;
}

