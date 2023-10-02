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

void ltrim(std::string& str) {
  str.erase(str.begin(), std::find_if(str.begin(), str.end(), [] (unsigned char c) {
    return !std::isspace(c);
  }));
}

void rtrim(std::string& str) {
  str.erase(std::find_if(str.rbegin(), str.rend(), [] (unsigned char c) {
    return !std::isspace(c);
  }).base(), str.end());
}

void trim(std::string& str) {
  rtrim(str);
  ltrim(str);
}

}
