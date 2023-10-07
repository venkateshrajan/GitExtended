#include "pch.h"
#include "git_wrapper.h"

#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/trim.hpp"
#include "glog/logging.h"
#include "utilities.h"

namespace gitex {

CGitCommand::CGitCommand(const std::string& gitcli) :
  gitcli(gitcli) {}


bool CGitCommand::diff_namestatus(FileStatusMap& files,
                       const std::list<std::string>& arguments) {
  std::string output;
  std::string error;
  std::list<std::string> args_to_process{"diff", "--name-status"};
  args_to_process.insert(args_to_process.end(), arguments.begin(), arguments.end());
  if (gitex::launch_process(gitcli, args_to_process, output, error) != 0) {
    LOG(ERROR) << "launch process failed for " << gitcli << 
      " diff --namestatus. Error lines: ";
    LOG(ERROR) << error;
    return false;
  }

  FileStatusMap result;
  std::vector<std::string> output_vec;
  boost::split(output_vec, output, boost::is_any_of("\n"));
  for (auto & item : output_vec) boost::trim(item);
  output_vec.erase(
    std::remove_if(
      output_vec.begin(),
      output_vec.end(),
      [](std::string const& s) {
        return s.empty();
      }),
    output_vec.end());
  if (!parse_status(output_vec, result)) {
    LOG(ERROR) << "Failed to parse result";
    return false;
  }

  files = result;

  return true;
}


bool CGitCommand::init(const std::list<std::string>& arguments) {
  std::string output;
  std::string error;
  std::list<std::string> args_to_process{"init"};
  args_to_process.insert(args_to_process.end(), arguments.begin(), arguments.end());
  if (gitex::launch_process(gitcli, args_to_process, output, error) != 0) {
    LOG(ERROR) << "launch process failed for " << gitcli << " init. Error lines: ";
    LOG(ERROR) << error;
    return false;
  }

  return true;
}


bool CGitCommand::root(std::string& path, 
                       const std::list<std::string>& arguments) {
  std::string error;
  std::list<std::string> args_to_process{"rev-parse", "--show-toplevel"};
  args_to_process.insert(args_to_process.end(), arguments.begin(), arguments.end());
  if (gitex::launch_process(gitcli, args_to_process, path, error) != 0) {
    LOG(ERROR) << "runCommand failed for " << gitcli 
      << " rev-parse --show-toplevel Error lines: ";
    LOG(ERROR) << error;
    return false;
  }

  boost::trim(path);

  return true;
}


bool CGitCommand::parse_status(const std::vector<std::string>& files, 
                  FileStatusMap& file_statuses) {

  for(std::string file_line : files) {
    std::vector<std::string> splits;
    boost::split(splits, file_line, boost::is_any_of(" \t\n\r"));

    if (splits.size() != 2) {
      LOG(ERROR) << "Expected two fields. line: " << file_line;
      return false;
    }

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
        LOG(ERROR) << "Invalid file status: " << splits[0][0];
        return false;
    }
  }

  return true;
}


}
