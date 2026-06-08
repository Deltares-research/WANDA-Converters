

add_library(pipeline_conversion STATIC
        model_converter.cpp
        model_converter.h
        mapping/from_wanda/wanda_model_importer.cpp
        mapping/from_wanda/wanda_model_importer.h
        mapping/from_wanda/wanda_pipe_importer.cpp
        mapping/from_wanda/wanda_pipe_importer.h
        core/typedef.h
        mapping/from_wanda/wanda_node_importer.cpp
        mapping/from_wanda/wanda_node_importer.h
        mapping/to_wanda/wanda_model_exporter.cpp
        mapping/to_wanda/wanda_model_exporter.h
        mapping/to_wanda/wanda_model_builder.cpp
        mapping/to_wanda/wanda_model_builder.h
        mapping/from_epanet/epanet_model_importer.cpp
        mapping/from_epanet/epanet_model_importer.h
        mapping/from_epanet/epanet_pipe_importer.cpp
        mapping/from_epanet/epanet_pipe_importer.h
        mapping/from_epanet/epanet_unit_converter.cpp
        mapping/from_epanet/epanet_unit_converter.h
        mapping/from_epanet/epanet_node_importer.cpp
        mapping/from_epanet/epanet_node_importer.h
        core/reservoir.h
        mapping/from_epanet/epanet_reservoir_importer.cpp
        mapping/from_epanet/epanet_reservoir_importer.h
        core/coordinates.h
        mapping/from_epanet/utility.cpp
        mapping/from_epanet/utility.h
        core/valve.h
        mapping/from_epanet/epanet_valve_importer.cpp
        mapping/from_epanet/epanet_valve_importer.h
)
set_target_properties(pipeline_conversion PROPERTIES LINKER_LANGUAGE CXX)
target_sources(pipeline_conversion
  PRIVATE
    core/node.h
    core/pipe.h
    core/network.h
    mapping/mapper_base.h
    utils/unit_converter.h
)
target_include_directories(pipeline_conversion
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        "${CMAKE_SOURCE_DIR}/libs/include/"
        ${epanet_SOURCE_DIR}/include
)

target_link_libraries(pipeline_conversion
        PUBLIC
        "${CMAKE_SOURCE_DIR}/libs/debug/Deltares.Wanda.lib"
        epanet2
)
