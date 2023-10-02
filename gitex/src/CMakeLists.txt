cmake_minimum_required (VERSION 3.22)

include_directories(${GitExtended_SOURCE_DIR})
include_directories(${GitExtended_SOURCE_DIR}/gitex/inc)
include_directories(${GitExtended_SOURCE_DIR}/libgitex/inc)

# Packages
find_package(absl CONFIG REQUIRED)
find_package(Boost)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable (gitex Main.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET gitex PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(gitex PRIVATE libgitex absl::strings ${Boost_LIBRARIES})


