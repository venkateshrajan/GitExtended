#include "pch.h"
#include "git_wrapper.h"

namespace gitex {

CCommandGitOp::CCommandGitOp(const std::string& gitcli) :
  gitcli(gitcli) {}

bool CCommandGitOp::diff_nameonly(std::vector<std::string>& files) {
  return true;
}

bool CCommandGitOp::init() {
  return true; 
}

bool CCommandGitOp::runCommand(const std::string& command, std::vector<std::string>& output) {
  return true;
}

}
