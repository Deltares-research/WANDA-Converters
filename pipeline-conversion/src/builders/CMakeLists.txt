add_library(pipeline_builders STATIC)
set_target_properties(pipeline_builders PROPERTIES LINKER_LANGUAGE CXX)

target_sources(pipeline_builders
  PRIVATE
    wanda_model_builder.h
)

target_include_directories(pipeline_builders
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
