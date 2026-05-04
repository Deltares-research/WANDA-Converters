#include "wanda_node_importer.h"

Node WandaNodeImporter::import(wanda_node &wandanode) const {
    return {
        .id = wandanode.get_name(),
        .elevation = wandanode.get_property("Elevation").get_scalar_float(),
        .position = wandanode.get_position()
    };
}

