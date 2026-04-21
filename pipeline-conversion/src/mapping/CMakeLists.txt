add_library(pipeline_mapping STATIC)
set_target_properties(pipeline_mapping PROPERTIES LINKER_LANGUAGE CXX)

target_sources(pipeline_mapping
  PRIVATE
    mapper_base.h
)

target_include_directories(pipeline_mapping
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
