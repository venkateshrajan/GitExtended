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



CGitDiffOperation::CGitDiffOperation() :
  IGitOperation() {
  
}


bool CGitDiffOperation::prepare()  {
  return true;
}


bool CGitDiffOperation::process()  {
  return true;
}


bool CGitDiffOperation::finalize()  {
  return true;
}

}
