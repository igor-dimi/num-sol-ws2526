cmake_minimum_required(VERSION 3.16)
project(numerics_solutions CXX)
set(CMAKE_CXX_STANDARD 20)

# Put binaries under build/bin/ubX/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# hdnum include dir (submodule at repo root)
set(HDNUM_DIR "../hdnum")

# Shared interface target with include path (and optional GMP)
add_library(hdnum_common INTERFACE)
target_include_directories(hdnum_common INTERFACE "${HDNUM_DIR}")

option(HDNUM_USE_GMP "Enable GMP in hdnum" OFF)
if(HDNUM_USE_GMP)
  target_compile_definitions(hdnum_common INTERFACE HDNUM_HAS_GMP=1)
  find_library(GMPXX gmpxx)
  find_library(GMP   gmp)
  if(GMPXX AND GMP)
    target_link_libraries(hdnum_common INTERFACE ${GMPXX} ${GMP})
  else()
    message(FATAL_ERROR "GMP not found; install libgmp-dev or disable HDNUM_USE_GMP")
  endif()
endif()

# Add each UB subdir in src/ if it has a CMakeLists.txt
foreach(ub IN ITEMS ub1 ub2 ub3 ub4 ub5 ub6 ub7 ub8 ub9 ub10)
  if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/${ub}/CMakeLists.txt")
    add_subdirectory("${ub}")
  endif()
endforeach()
