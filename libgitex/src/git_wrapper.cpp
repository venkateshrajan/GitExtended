#include "pch.h"
#include "git_wrapper.h"

#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/process.hpp"

namespace bp = boost::process;

namespace gitex {

CGitCommand::CGitCommand(const std::string& gitcli) :
  gitcli(gitcli) {}


bool CGitCommand::diff_namestatus(FileStatusMap& files) {
  std::vector<std::string> output;
  std::vector<std::string> error;
  // TODO: Add logs
  if (runCommand(output, error, "diff", "--name-status") != 0) return false;

  // TODO: Add logs
  FileStatusMap result;
  if (!parse_status(output, result)) return false;

  files = result;

  return true;
}


bool CGitCommand::init() {
  std::vector<std::string> output;
  std::vector<std::string> error;
  // TODO: Add logs
  if (runCommand(output, error, "init") != 0) return false;

  return true;
}


bool CGitCommand::root(std::string& path) {
  std::vector<std::string> output;
  std::vector<std::string> error;
  // TODO: Add logs
  if (runCommand(output, error, "rev-parse", "--show-toplevel") != 0) return false;

  // TODO: Add logs
  if (output.size() != 1) return false;

  path = output[0];

  return true;
}


template<typename... Args>
int CGitCommand::runCommand(std::vector<std::string>& output,
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


bool CGitCommand::parse_status(const std::vector<std::string>& files, 
                  FileStatusMap& file_statuses) {

  for(std::string file_line : files) {
    std::vector<std::string> splits;
    boost::split(splits, file_line, boost::is_any_of(" \t\n\r"));

    // TODO: Add logs
    if (splits.size() != 2) return false;

    switch(splits[0][0]) {
    case 'M':
        file_statuses[splits[1]] = status::status_modified;
        break;
    case 'C':
        file_statuses[splits[1]] = status::status_copy_edit;
        break;
    case 'R':
        file_statuses[splits[1]] = status::status_rename_edit;
        break;
    case 'A':
        file_statuses[splits[1]] = status::status_added;
        break;
    case 'D':
        file_statuses[splits[1]] = status::status_deleted;
        break;
    case 'U':
        file_statuses[splits[1]] = status::status_unmerged;
        break;
    default:
        // TODO: Add logs
        return false;
    }
  }

  return true;
}


}
