#include "pch.h"

#include <boost/program_options.hpp>
#include <git_wrapper.h>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help", "prints this message")
    ("copy", "copies git files to the specified location")
    ("diff", "operations on top of git diff")
    ("init", "initializes the git repository")
  ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help") || argc <= 1) {
    std::cout << desc << std::endl;
    return 0;
  }

  gitex::CCommandGitOp git("git");

  gitex::FileStatusMap files;
  if (!git.diff_namestatus(files)) {
    std::cout<< "diff name status failed" << std:: endl;
    return 1;
  }

  for (auto const& [file, status] : files)
    std::cout<< file << status << std::endl;

  return 0;
}

