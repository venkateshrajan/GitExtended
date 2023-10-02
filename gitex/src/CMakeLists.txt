cmake_minimum_required (VERSION 3.22)

include_directories(${GitExtended_SOURCE_DIR})
include_directories(${GitExtended_SOURCE_DIR}/gitex/inc)
include_directories(${GitExtended_SOURCE_DIR}/libgitex/inc)

find_package(Boost 1.83.0 COMPONENTS program_options)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})

  add_executable (gitex Main.cpp)

  target_link_libraries(gitex PRIVATE libgitex ${Boost_LIBRARIES})
endif()

