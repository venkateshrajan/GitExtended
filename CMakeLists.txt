# CMakeList.txt : CMake project for GitExtended, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.22)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("GitExtended")
include ("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

# Packages
find_package(absl CONFIG REQUIRED)

set(SOURCES
  GitExtended.cpp
  GitExtended.h
  pch.h
  utilities.cpp
  utilities.h
) 

add_executable (gitex ${SOURCES} Main.cpp)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET gitex PROPERTY CXX_STANDARD 20)
endif()

target_precompile_headers(gitex PUBLIC pch.h)
target_link_libraries(gitex PRIVATE absl::strings)


# TODO: Add tests and install targets if needed.
include (CTest)
find_package(GTest CONFIG REQUIRED)
add_executable(gitex_test ${SOURCES} tests.cpp)

target_precompile_headers(gitex_test PUBLIC pch.h)
target_link_libraries(gitex_test PRIVATE absl::strings GTest::gtest GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(gitex_test)
