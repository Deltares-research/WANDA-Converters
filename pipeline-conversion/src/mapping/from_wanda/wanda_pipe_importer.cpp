#include "wanda_pipe_importer.h"
#include "wandanode.h"
#include <string>

Pipe WandaPipeImporter::import(wanda_component &wandacomponent) const {
    const double inner_diameter = wandacomponent.get_property("Inner diameter").get_scalar_float();
    const double wall_roughness = wandacomponent.get_property("Wall roughness").get_scalar_float();
    const double length = wandacomponent.get_property("Length").get_scalar_float();
    const NodeId from_id = wandacomponent.get_connected_node(1).get_complete_name_spec();
    const NodeId to_id = wandacomponent.get_connected_node(2).get_complete_name_spec();;
    const ComponentId name = wandacomponent.get_name();
    return {
        .name = name,
        .length = length,
        .inner_diameter = inner_diameter,
        .wall_roughness = wall_roughness,
        .from_node_id = from_id,
        .to_node_id = to_id,
        .position = wandacomponent.get_position()
    };
}

