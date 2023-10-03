cmake_minimum_required (VERSION 3.22)

project ("GitExtended")

include ("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost 1.83.0 COMPONENTS program_options)

add_subdirectory(gitex)
add_subdirectory(libgitex)
add_subdirectory(tests)

target_precompile_headers(gitex PRIVATE pch.h)
target_precompile_headers(libgitex PRIVATE pch.h)
target_precompile_headers(gitex_test PRIVATE pch.h)
