#include "pch.h"

#include "args.hxx"
#include "glog/logging.h"
#include "git_operation.h"
#include <iterator>

void DiffCommand(args::Subparser &parser) {
  args::ValueFlag<std::string> copy(parser, 
                                    "", 
                                    "Copy diff files to the specified location",
                                    {'c', "copy"});
  args::PositionalList<std::string> arguments(parser,
                      "arguments", "Arguments for git diff command");
  args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
  parser.Parse();

  if(copy) {
    gitex::CGitDiffOperation diff(args::get(copy));
    std::vector<std::string> vec_args;
    if (arguments) vec_args = args::get(arguments);
    if (!diff.run(
      std::list<std::string>(
        std::make_move_iterator(std::begin(vec_args)),
        std::make_move_iterator(std::end(vec_args)))
    ))
      std::cout << "gitex diff copy operation failed" << std::endl;
  } else {
    std::cout << "Argument required: use 'gitex diff -h' to get help" << std::endl;
  }
}

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

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

