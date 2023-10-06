#include "pch.h"
#include "git_operation.h"

#include "git_wrapper.h"
#include <glog/logging.h>

namespace gitex {

IGitOperation::IGitOperation() {
  git = std::make_shared<CGitCommand>("git");
}


bool IGitOperation::run(const std::vector<std::string>& arguments) {
  if (!prepare(arguments)) {
    LOG(ERROR) << "Prepare failed";
    return false;
  }

  if (!process(arguments)) {
    LOG(ERROR) << "Process failed";
    return false;
  }

  if (!finalize(arguments)) {
    LOG(ERROR) << "Finalize failed";
    return false;
  }

  return true;
}


bool IGitOperation::prepare(const std::vector<std::string>& arguments) {
  if (!git->root(root)) {
    LOG(ERROR) << "Failed to get the root path";
    return false;
  }

  return true;
}


bool IGitOperation::finalize(const std::vector<std::string>& arguments) {
  return true;
}



CGitDiffOperation::CGitDiffOperation(const std::string& copyPath) :
  IGitOperation(),
  copyPath(copyPath) {
  
}


bool CGitDiffOperation::process(const std::vector<std::string>& arguments)  {
  std::cout<< root << " " << copyPath << " ";
  for (const auto& arg : arguments) std::cout << arg << " ";
  std::cout<< std::endl;

  return true;
}


}
