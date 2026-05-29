#pragma once
#include "typedef.h"
#include <vector>
#include "coordinates.h"

/**
 * @brief Represents a node (junction point) in the pipeline network.
 *
 * Fields:
 * - id        : Unique identifier of the node.
 * - elevation : Elevation of the node above a reference datum.
 */
struct Node {
  NodeId id;
  double elevation;
  double base_demand;
  DiagramCoordinates position;
};
