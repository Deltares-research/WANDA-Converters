#pragma once


struct Pipe {
  int from_node_id{0};
  int to_node_id{0};
  double length{0};
  double inner_diameter{0};
  double wall_roughness{0};
};

