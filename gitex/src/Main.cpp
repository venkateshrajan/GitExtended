#include "pch.h"

#include <boost/program_options.hpp>
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

  std::cout << "hello world!" << std::endl;
}

