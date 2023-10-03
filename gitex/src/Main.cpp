#include "pch.h"

#include <args.hxx>
#include <git_wrapper.h>


void DiffCommand(args::Subparser &parser) {
  args::ValueFlag<std::string> copy(parser, 
                                    "", 
                                    "Copy diff files to the specified location",
                                    {'c', "copy"});
  args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
  parser.Parse();

  if(copy) {
    std::cout << "Copy " << args::get(copy) << std::endl;
  } else {
    std::cout << "Argument required: use 'gitex diff -h' to get help" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  args::ArgumentParser parser(
    "Git extended operations", 
    "'gitex command -h' to read about a specfic command");
  args::Group commands(parser, "commands");
  args::Command diff(commands, "diff", "diff related operations", &DiffCommand);
  args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
  args::CompletionFlag completion(parser, {"complete"});

  try {
    parser.ParseCLI(argc, argv);
  } catch (const args::Completion& e) {
    std::cout << e.what();
    return 0;
  } catch (const args::Help&) {
    std::cout << parser;
    return 0;
  } catch (const args::ParseError& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << parser;
    return 1;
  } catch (const args::ValidationError& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << parser;
    return 1;
  }

  return 0;
}

