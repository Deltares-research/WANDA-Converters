add_library(pipeline_conversion STATIC)
set_target_properties(pipeline_conversion PROPERTIES LINKER_LANGUAGE CXX)
target_sources(pipeline_conversion
  PRIVATE
    core/node.h
    core/pipe.h
    core/network.h
    mapping/mapper_base.h
    descriptors/wanda_pipe_descriptor.h
    builders/wanda_model_builder.h
    utils/unit_converter.h
)
target_include_directories(pipeline_conversion
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/mapping
    ${CMAKE_CURRENT_SOURCE_DIR}/descriptors
    ${CMAKE_CURRENT_SOURCE_DIR}/builders
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)
