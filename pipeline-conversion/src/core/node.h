#pragma once
#include "typedef.h"

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
  std::vector<float> position;
};
