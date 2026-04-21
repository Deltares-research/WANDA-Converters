add_library(pipeline_core STATIC)
set_target_properties(pipeline_core PROPERTIES LINKER_LANGUAGE CXX)

target_sources(pipeline_core
  PRIVATE
    node.h
    pipe.h
    network.h
)

target_include_directories(pipeline_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
