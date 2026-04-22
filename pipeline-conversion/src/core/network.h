#pragma once

#include <vector>

#include "node.h"
#include "pipe.h"

struct Network {
  std::vector<Node> nodes;
  std::vector<Pipe> pipes;
};
