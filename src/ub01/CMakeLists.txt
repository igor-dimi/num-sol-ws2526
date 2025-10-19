set(UB ub1)

# Group executables per UB on disk (and per-config for multi-config generators)
set(OUT "${CMAKE_BINARY_DIR}/bin/${UB}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUT}")
foreach(cfg IN ITEMS Debug Release RelWithDebInfo MinSizeRel)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${cfg} "${OUT}/${cfg}")
endforeach()

function(add_ub_example name)
  add_executable(${name} "${name}.cpp")
  target_link_libraries(${name} PRIVATE hdnum_common)
  set_target_properties(${name} PROPERTIES FOLDER "${UB}") # IDE grouping
endfunction()

# List ub1 binaries here:
# add_ub_example(ub1_task1)
