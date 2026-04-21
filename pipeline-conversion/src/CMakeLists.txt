add_library(pipeline_core STATIC)
set_target_properties(pipeline_core PROPERTIES LINKER_LANGUAGE CXX)
target_sources(pipeline_core
  PRIVATE
    core/node.h
    core/pipe.h
    core/network.h
)
target_include_directories(pipeline_core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core
)

add_library(pipeline_mapping STATIC)
set_target_properties(pipeline_mapping PROPERTIES LINKER_LANGUAGE CXX)
target_sources(pipeline_mapping
  PRIVATE
    mapping/mapper_base.h
)
target_include_directories(pipeline_mapping
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/mapping
)

add_library(pipeline_descriptors STATIC)
set_target_properties(pipeline_descriptors PROPERTIES LINKER_LANGUAGE CXX)
target_sources(pipeline_descriptors
  PRIVATE
    descriptors/wanda_pipe_descriptor.h
)
target_include_directories(pipeline_descriptors
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/descriptors
)

add_library(pipeline_builders STATIC)
set_target_properties(pipeline_builders PROPERTIES LINKER_LANGUAGE CXX)
target_sources(pipeline_builders
  PRIVATE
    builders/wanda_model_builder.h
)
target_include_directories(pipeline_builders
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/builders
)

add_library(pipeline_utils STATIC)
set_target_properties(pipeline_utils PROPERTIES LINKER_LANGUAGE CXX)
target_sources(pipeline_utils
  PRIVATE
    utils/unit_converter.h
)
target_include_directories(pipeline_utils
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

target_link_libraries(pipeline_builders
  PUBLIC
    pipeline_core
    pipeline_descriptors
    pipeline_mapping
)
