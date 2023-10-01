# CMakeList.txt : CMake project for GitExtended, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GitExtended")

include ("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

enable_testing()

# Packages
find_package(absl CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(SOURCES
  GitExtended.cpp
  GitExtended.h
  Main.cpp
  pch.h
  tests.cpp
) 

# Add source to this project's executable.
add_executable (GitExtended ${SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET GitExtended PROPERTY CXX_STANDARD 20)
endif()

# pch.h
target_precompile_headers(GitExtended PUBLIC pch.h)

# Linking libraries
target_link_libraries(GitExtended PRIVATE absl::strings GTest::gtest GTest::gtest_main)


# TODO: Add tests and install targets if needed.
add_test(AllTests GitExtended)

