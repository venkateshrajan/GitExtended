#include "pch.h"
#include "git_wrapper.h"

#include <boost/process.hpp>
namespace bp = boost::process;

namespace gitex {

CCommandGitOp::CCommandGitOp(const std::string& gitcli) :
  gitcli(gitcli) {}


bool CCommandGitOp::diff_namestatus(std::vector<std::string>& files) {
  std::vector<std::string> error;
  if (runCommand(files, error, "diff", "--name-status") != 0) {
    // TODO: Add logs
    // for (std::string err: error)
    //   std::cout << err << std::endl;
    return false;
  }

  return true;
}


bool CCommandGitOp::init() {
  std::vector<std::string> output;
  std::vector<std::string> error;
  if (runCommand(output, error, "init") != 0) {
    // TODO: Add logs
    return false;
  }

  return true;
}


template<typename... Args>
int CCommandGitOp::runCommand(std::vector<std::string>& output,
               std::vector<std::string>& error,
               Args... args) {
  bp::ipstream out_stream;
  bp::ipstream err_stream;
  bp::child c(bp::search_path(gitcli.c_str()), 
              args..., 
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
