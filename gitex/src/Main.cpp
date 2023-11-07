#include "pch.h"

#include "args.hxx"
#include "glog/logging.h"
#include "git_operation.h"
#include <iterator>

// TODO: Move this into pch.h
#ifdef __unix__
#include <unistd.h>
#elif defined _WIN32
struct IUnknown; // why is windows making me do this?
#include <windows.h>
#define sleep(x) Sleep(1000 * (x))
#endif

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

void CopyCommand(args::Subparser &parser) {
  args::ValueFlag<std::string> input(parser, 
                                    "", 
                                    "Copy diff files to the specified location",
                                    {'i', "input-file"});
  args::Positional<std::string> path(parser,
                      "path", "Destination path where the files need to get copied");
  args::PositionalList<std::string> arguments(parser,
                      "arguments", "Arguments for copy command");
  args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
  parser.Parse();

  gitex::CGitCopyOperation copyop(args::get(input), args::get(path));
  std::vector<std::string> vec_args;
  if (arguments) vec_args = args::get(arguments);
  if (!copyop.run(
        std::list<std::string>(
          std::make_move_iterator(std::begin(vec_args)),
          std::make_move_iterator(std::end(vec_args)))
        ))
    std::cout << "gitex diff copy operation failed" << std::endl;
}
int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  std::filesystem::path debug_path(".");
  debug_path /= std::filesystem::path("debug");
  if (std::filesystem::exists(debug_path))
    while(true) sleep(1000);

  args::ArgumentParser parser(
    "Git extended operations", 
    "'gitex command -h' to read about a specfic command");
  args::Group commands(parser, "commands");
  args::Command diff(commands, "diff", "diff related operations", &DiffCommand);
  args::Command copy(commands, "copy", "copy related operations", &CopyCommand);
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

