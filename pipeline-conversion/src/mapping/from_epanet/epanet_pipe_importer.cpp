#include "epanet_pipe_importer.h"

#include "epanet_unit_converter.h"
#include "utility.h"
#include "core/typedef.h"

Pipe EpanetPipeImporter::import(EN_Project ph, int link_index, const EpanetUnitConverter& unit_converter) const {
    Pipe pipe{};

    // --- Pipe ID ---
    char link_id[EN_MAXID + 1];
    EN_getlinkid(ph, link_index, link_id);
    pipe.name = ComponentId{link_id};

    // --- Connectivity ---
    int from_node_idx = 0;
    int to_node_idx   = 0;
    EN_getlinknodes(ph, link_index, &from_node_idx, &to_node_idx);

    char from_id[EN_MAXID + 1];
    char to_id[EN_MAXID + 1];
    EN_getnodeid(ph, from_node_idx, from_id);
    EN_getnodeid(ph, to_node_idx, to_id);

    pipe.from_node_id = NodeId{from_id};
    pipe.to_node_id   = NodeId{to_id};

    // --- Geometry ---
    double value = 0.0;

    EN_getlinkvalue(ph, link_index, EN_LENGTH, &value);
    pipe.length = unit_converter.convert_length_to_si(value);

    EN_getlinkvalue(ph, link_index, EN_DIAMETER, &value);
    pipe.inner_diameter = unit_converter.convert_diameter_to_si(value);

    EN_getlinkvalue(ph, link_index, EN_ROUGHNESS, &value);
    pipe.friction_model_roughness = unit_converter.convert_roughness_to_si(value);         // depends on headloss formula

    pipe.position = get_link_coordinates(ph, link_index);

    return pipe;
}
