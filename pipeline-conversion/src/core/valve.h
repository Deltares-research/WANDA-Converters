#ifndef PIPELINE_CONVERSION_VALVE_H
#define PIPELINE_CONVERSION_VALVE_H
#include <vector>

#include "coordinates.h"
#include "typedef.h"

enum class ValveType {
    PRV,
    PSV,
    PBV,
    FCV,
    TCV,
    PCV,
    GPV
};

struct Valve {
    ComponentId name;
    NodeId from_node_id;
    NodeId to_node_id;
    double inner_diameter{0};
    ValveType valve_type{ValveType::PRV};
    double loss_coefficient{0};
    std::vector<DiagramCoordinates> position;
};

#endif //PIPELINE_CONVERSION_VALVE_H
