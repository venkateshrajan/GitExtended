#pragma once

namespace gitex {

int launch_process(const std::string& exe,
                   const std::list<std::string>& arguments,
                   std::string& output);
int launch_process(const std::string& exe,
                   const std::list<std::string>& arguments,
                   std::string& output,
                   std::string& error);
}
