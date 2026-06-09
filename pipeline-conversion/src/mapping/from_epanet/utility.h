#ifndef PIPELINE_CONVERSION_UTILITY_H
#define PIPELINE_CONVERSION_UTILITY_H

#include <vector>

#include "core/coordinates.h"
#include "epanet2_2.h"

DiagramCoordinates get_coordinates(EN_Project ph, int node_index);
std::vector<DiagramCoordinates> get_vertex(EN_Project ph, int link_index);
std::vector<DiagramCoordinates> get_link_coordinates(EN_Project ph, int link_index);

#endif // PIPELINE_CONVERSION_UTILITY_H