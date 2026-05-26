//
// Created by zwan on 26/05/2026.
//

#include "epanet_reservoir_importer.h"

Reservoir EpanetReservoirImporter::import(const EN_Project ph, const int node_index,
    const EpanetUnitConverter &unit_converter) const {
    Reservoir reservoir;
    // --- Node ID ---
    char node_id[EN_MAXID + 1];
    EN_getnodeid(ph, node_index, node_id);
    reservoir.name = NodeId{node_id};
    double value = 0.0;
    EN_getnodevalue(ph, node_index, EN_HEAD, &value);
    reservoir.head = unit_converter.convert_length_to_si(value);
    reservoir.position = {0, 0}; // TODO: get actual position from EPANET model (if available)

    return reservoir;
}
