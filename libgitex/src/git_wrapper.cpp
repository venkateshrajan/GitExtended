#include "pch.h"
#include "git_wrapper.h"

#include <boost/process.hpp>
namespace bp = boost::process;

namespace gitex {

CCommandGitOp::CCommandGitOp(const std::string& gitcli) :
  gitcli(gitcli) {}

bool CCommandGitOp::diff_nameonly(std::vector<std::string>& files) {
  return true;
}

bool CCommandGitOp::init() {
  return true; 
}

int CCommandGitOp::runCommand(const std::string& arguments, 
               std::vector<std::string>& output,
               std::vector<std::string>& error) {
  bp::ipstream out_stream;
  bp::ipstream err_stream;
  bp::child c(bp::search_path(gitcli.c_str()), 
              arguments.c_str(), 
              bp::std_out > out_stream, 
              bp::std_err > err_stream);

  std::string line;
  while (out_stream && std::getline(out_stream, line) && !line.empty())
    output.push_back(line);

  line.clear();
  while (err_stream && std::getline(err_stream, line) && !line.empty())
    error.push_back(line);

  c.wait();

  return c.exit_code();
}

}
