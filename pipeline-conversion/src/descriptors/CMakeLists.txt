add_library(pipeline_descriptors STATIC)
set_target_properties(pipeline_descriptors PROPERTIES LINKER_LANGUAGE CXX)

target_sources(pipeline_descriptors
  PRIVATE
    wanda_pipe_descriptor.h
)

target_include_directories(pipeline_descriptors
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
