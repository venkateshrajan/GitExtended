cmake_minimum_required (VERSION 3.22)

include_directories(${GitExtended_SOURCE_DIR})
include_directories(${GitExtended_SOURCE_DIR}/libgitex/inc)

set(SOURCES
  GitExtended.cpp
  utilities.cpp
) 

add_library(libgitex ${SOURCES})
