#include "epanet_valve_importer.h"

#include <stdexcept>

#include "utility.h"

Valve EpanetValveImporter::import(const EN_Project ph, const int link_index, const EpanetUnitConverter& unit_converter) const {
    Valve valve{};
    // --- Valve ID ---
    char link_id[EN_MAXID + 1];
    EN_getlinkid(ph, link_index, link_id);
    valve.name = ComponentId{link_id};

    // --- Connectivity ---
    int from_node_idx = 0;
    int to_node_idx   = 0;
    EN_getlinknodes(ph, link_index, &from_node_idx, &to_node_idx);

    char from_id[EN_MAXID + 1];
    char to_id[EN_MAXID + 1];
    EN_getnodeid(ph, from_node_idx, from_id);
    EN_getnodeid(ph, to_node_idx, to_id);

    valve.from_node_id = NodeId{from_id};
    valve.to_node_id   = NodeId{to_id};

    // --- Geometry ---
    double value = 0.0;

    EN_getlinkvalue(ph, link_index, EN_DIAMETER, &value);
    valve.inner_diameter = unit_converter.convert_diameter_to_si(value);

    EN_getlinkvalue(ph, link_index, EN_MINORLOSS, &value);
    valve.loss_coefficient = value;

    valve.position = get_link_coordinates(ph, link_index);
    EN_getlinkvalue(ph, link_index, EN_VALVE_TYPE, &value);
    switch (static_cast<int>(value)) {
        case EN_PRV:
            valve.valve_type = ValveType::PRV;
            break;
        case EN_PSV:
            valve.valve_type = ValveType::PSV;
            break;
        case EN_PBV:
            valve.valve_type = ValveType::PBV;
            break;
        case EN_FCV:
            valve.valve_type = ValveType::FCV;
            break;
        case EN_TCV:
            valve.valve_type = ValveType::TCV;
            break;
        case EN_PCV:
            valve.valve_type = ValveType::PCV;
            break;
        case EN_GPV:
            valve.valve_type = ValveType::GPV;
            break;
        default:
            throw std::invalid_argument("Invalid valve type");
    }
    return valve;
}
