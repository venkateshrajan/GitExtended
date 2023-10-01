#include "pch.h"

namespace util {

/* Executes the system command and gathers the output in vector<string>
 * Input: 
 *  command => System command to be executed
 * Output:
 *  output => Each line is added to the vector 
 */
int executeCommand(const std::string& command, std::vector<std::string>& output);

}
