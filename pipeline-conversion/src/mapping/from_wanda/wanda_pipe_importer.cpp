#include "wanda_pipe_importer.h"

#include <string>

Pipe WandaPipeImporter::import(wanda_component &wandacomponent) const {
    const double inner_diameter = wandacomponent.get_property("Inner diameter").get_scalar_float();
    const double wall_roughness = wandacomponent.get_property("Wall roughness").get_scalar_float();
    const double length = wandacomponent.get_property("Length").get_scalar_float();
    const std::string from_id = "test";
    const std::string to_id = "test";
    return {
        .length = length,
        .inner_diameter = inner_diameter,
        .wall_roughness = wall_roughness
    };
}

