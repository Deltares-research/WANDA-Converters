#ifndef WANDAAPI_WANDAGRAPHMAPPER_H
#define WANDAAPI_WANDAGRAPHMAPPER_H
#include <vector>
#include "wandacomponent.h"
#include "Wandagraph.h"

WandaGraph create_graph( const std::unordered_map<std::string, wanda_component>& phys_components);
std::vector<EdgeInput> convert_component_to_edges(const wanda_component& comp);
std::vector<EdgeInput> convert_boundary_component_to_edges(const wanda_component& comp);
std::vector<EdgeInput> convert_fall_component_to_edges(const wanda_component& comp);
std::vector<EdgeInput> convert_T_component_to_edges(const wanda_component& comp);
std::vector<EdgeInput> convert_cross_component_to_edges(const wanda_component& comp);

#endif //WANDAAPI_WANDAGRAPHMAPPER_H