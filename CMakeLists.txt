cmake_minimum_required (VERSION 3.22)

project ("GitExtended")

include ("$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")

add_subdirectory(gitex)
add_subdirectory(libgitex)
add_subdirectory(tests)

target_precompile_headers(gitex PRIVATE pch.h)
target_precompile_headers(libgitex PRIVATE pch.h)
target_precompile_headers(gitex_test PRIVATE pch.h)
