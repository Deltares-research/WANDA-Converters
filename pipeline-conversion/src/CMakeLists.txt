

add_library(pipeline_conversion STATIC
        mapping/from_wanda/wanda_pipe_to_entity_mapper.cpp
        mapping/from_wanda/wanda_pipe_to_entity_mapper.h
        model_converter.cpp
        model_converter.h
        mapping/from_wanda/wanda_model_importer.cpp
        mapping/from_wanda/wanda_model_importer.h
        mapping/from_wanda/wanda_pipe_importer.cpp
        mapping/from_wanda/wanda_pipe_importer.h
        core/typedef.h
        mapping/from_wanda/wanda_node_importer.cpp
        mapping/from_wanda/wanda_node_importer.h)
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
    ${CMAKE_CURRENT_SOURCE_DIR}
    "${CMAKE_SOURCE_DIR}/libs/include/"
)

target_link_libraries(pipeline_conversion
  PUBLIC
"${CMAKE_SOURCE_DIR}/libs/debug/Deltares.Wanda.lib"
)
