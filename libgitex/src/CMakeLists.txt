cmake_minimum_required (VERSION 3.22)

include_directories(${GitExtended_SOURCE_DIR})
include_directories(${GitExtended_SOURCE_DIR}/libgitex/inc)

find_package(Boost 1.83.0 COMPONENTS filesystem)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})

  set(SOURCES
    git_wrapper.cpp
  ) 

  add_library(libgitex ${SOURCES})
  target_link_libraries(libgitex PRIVATE ${Boost_LIBRARIES})
endif()


