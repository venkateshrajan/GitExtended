#include "pch.h"
#include "git_operation.h"

#include "git_wrapper.h"
#include <glog/logging.h>

namespace gitex {

IGitOperation::IGitOperation() {
  git = std::make_shared<CGitCommand>("git");
}


bool IGitOperation::run() {
  if (!prepare()) {
    LOG(ERROR) << "Prepare failed";
    return false;
  }

  if (!process()) {
    LOG(ERROR) << "Process failed";
    return false;
  }

  if (!finalize()) {
    LOG(ERROR) << "Finalize failed";
    return false;
  }

  return true;
}


bool IGitOperation::prepare() {
  if (!git->root(root)) {
    LOG(ERROR) << "Failed to get the root path";
    return false;
  }

  return true;
}


bool IGitOperation::finalize() {
  return true;
}



CGitDiffOperation::CGitDiffOperation(const std::string& copyPath) :
  IGitOperation(),
  copyPath(copyPath) {
  
}


bool CGitDiffOperation::process()  {
  std::cout<< root << " " << copyPath << std::endl;
  return true;
}


}
