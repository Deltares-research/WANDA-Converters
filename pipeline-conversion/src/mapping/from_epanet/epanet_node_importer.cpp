#include "epanet_node_importer.h"

#include "core/typedef.h"

Node EpanetNodeImporter::import(EN_Project ph, int node_index, const EpanetUnitConverter& unit_converter) const {
    Node node{};

    // --- Node ID ---
    char node_id[EN_MAXID + 1];
    EN_getnodeid(ph, node_index, node_id);
    node.id = NodeId{node_id};

    // --- Elevation ---
    double value = 0.0;
    EN_getnodevalue(ph, node_index, EN_ELEVATION, &value);
    node.elevation = unit_converter.convert_length_to_si(value);
    EN_getnodevalue(ph, node_index, EN_BASEDEMAND, &value);
    node.base_demand = unit_converter.convert_flow_to_si(value);
    node.position = {0, 0}; // TODO: get actual position from EPANET model (if available)

    return node;
}

