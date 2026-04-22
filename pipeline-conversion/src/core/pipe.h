#pragma once
#include <string>


struct Pipe {
  std::string from_node_id;
  std::string to_node_id;
  std::string name;
  double length{0};
  double inner_diameter{0};
  double wall_roughness{0};
};


