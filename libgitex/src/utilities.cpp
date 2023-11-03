#include "pch.h"
#include "utilities.h"

#include "boost/process/v2.hpp"
#include "boost/asio.hpp"

namespace boost_proc = boost::process::v2;
namespace asio = boost::asio;

namespace gitex {

int launch_process(const std::string &exe, 
                   const std::list<std::string> &arguments,
                   std::string& output) {
  std::string error;
  return launch_process(exe, arguments, output, error);
}

int launch_process(const std::string &exe, 
                   const std::list<std::string> &arguments,
                   std::string& output,
                   std::string& error) {
  asio::io_context ctx;
  asio::readable_pipe o{ctx};
  asio::readable_pipe e{ctx};

  const auto exe_found = boost_proc::environment::find_executable(exe);
  boost_proc::process c{ctx, exe_found, arguments, boost_proc::process_stdio{nullptr, o, e}};

  boost::system::error_code ec;
  auto sz = asio::read(o, asio::dynamic_buffer(output), ec);
  auto err = asio::read(e, asio::dynamic_buffer(error), ec);

  c.wait();
  
  return c.exit_code();
}

}
