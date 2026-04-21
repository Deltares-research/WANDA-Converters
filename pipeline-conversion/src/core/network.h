#pragma once

#include <vector>

#include "node.h"
#include "pipe.h"

namespace pipeline::core {

struct Network {
  std::vector<Node> nodes;
  std::vector<Pipe> pipes;
};

} // namespace pipeline::core
