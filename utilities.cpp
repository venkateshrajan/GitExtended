#include "pch.h"
#include "utilities.h"

namespace util {

int executeCommand(const std::string& command, std::vector<std::string>& output) {
  std::FILE *fp = popen(command.c_str(), "r");
  if (fp == NULL)
    return 1;

  char *line = nullptr;
  size_t len = 0;
  while(getline(&line, &len, fp) != -1)
    output.push_back(line);

  pclose(fp);

  if (line)
    free(line);

  // TODO: get the exit status of the command
  return 0;
}

}
