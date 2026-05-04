#pragma once

#include <vector>

#include "node.h"
#include "pipe.h"

/**
 * @brief Represents a pipeline network consisting of nodes and pipes.
 *
 * Fields:
 * - nodes : Collection of all Node objects in the network.
 * - pipes : Collection of all Pipe objects connecting the nodes.
 */
struct Network {
  std::vector<Node> nodes;
  std::vector<Pipe> pipes;
};
