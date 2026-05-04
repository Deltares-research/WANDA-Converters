#pragma once
#include <string>
#include <vector>

#include "typedef.h"

/**
 * @brief Represents a pipe element in the pipeline network.
 *
 * Fields:
 * - name            : Unique component identifier of the pipe.
 * - length          : Length of the pipe.
 * - inner_diameter  : Inner diameter of the pipe.
 * - wall_roughness  : Wall roughness of the pipe.
 * - from_node_id    : Identifier of the upstream node.
 * - to_node_id      : Identifier of the downstream node.
 */
struct Pipe {
  ComponentId name;
  double length{0};
  double inner_diameter{0};
  double wall_roughness{0};
  NodeId from_node_id;
  NodeId to_node_id;
  std::vector<float> position;
};
