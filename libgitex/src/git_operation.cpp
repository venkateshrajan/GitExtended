#include "pch.h"
#include "git_operation.h"

#include "git_wrapper.h"

namespace gitex {

IGitOperation::IGitOperation() {
  git = std::make_shared<CGitCommand>("git");
}


bool IGitOperation::run() {
  // TODO: Add logs
  if (!prepare()) return false;

  // TODO: Add logs
  if (!process()) return false;
  //
  // TODO: Add logs
  if (!finalize()) return false;

  return true;
}


bool IGitOperation::prepare() {
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
  return true;
}


}
