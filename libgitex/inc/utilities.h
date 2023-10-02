#include "pch.h"

namespace util {

/////////////////////////////////////////////////////////////
/// Process/command related APIs
/////////////////////////////////////////////////////////////

/* Executes the system command and gathers the output in vector<string>
 * Input: 
 *  command => System command to be executed
 * Output:
 *  output => Each line is added to the vector 
 */
int executeCommand(const std::string& command, std::vector<std::string>& output);


/////////////////////////////////////////////////////////////
/// string APIs
/////////////////////////////////////////////////////////////

/* Trim whitespaces at the left of a string */
void ltrim(std::string& str);

/* Trim whitespaces at the right of a string */
void rtrim(std::string& str);

/* Trim whitespaces at both the ends of a string */
void trim(std::string& str);

}
