#pragma once
#include <string>
#include "typedef.h"

struct Pipe {
  ComponentId name;
  double length{0};
  double inner_diameter{0};
  double wall_roughness{0};
  NodeId from_node_id;
  NodeId to_node_id;
};


