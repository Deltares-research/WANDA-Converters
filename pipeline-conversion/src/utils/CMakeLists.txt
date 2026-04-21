add_library(pipeline_utils STATIC)
set_target_properties(pipeline_utils PROPERTIES LINKER_LANGUAGE CXX)

target_sources(pipeline_utils
  PRIVATE
    unit_converter.h
)

target_include_directories(pipeline_utils
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
