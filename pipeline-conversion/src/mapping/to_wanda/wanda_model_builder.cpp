#include "wanda_model_builder.h"
#include <string>

constexpr const char* WANDABIN = R"(c:\Program Files (x86)\Deltares\Wanda 4.8\Bin64\)";

WandaModelBuilder::WandaModelBuilder(const std::string &wanda_file): model_(wanda_file, WANDABIN) {
}

void WandaModelBuilder::add_node(const Node &node) {

    auto& wanda_node = model_.add_node("Hydraulic node",node.position, node.id);
    wanda_node.get_property("Elevation").set_scalar(static_cast<float>(node.elevation));
}

void WandaModelBuilder::add_pipe(const Pipe &pipe) {
    std::vector<float> position = {0,0};
    auto& wanda_pipe =model_.add_component("Pipe (Liquid)",pipe.position, pipe.name);
    wanda_pipe.get_property("Length").set_scalar(static_cast<float>(pipe.length));
    wanda_pipe.get_property("Inner diameter").set_scalar(static_cast<float>(pipe.inner_diameter));
    wanda_pipe.get_property("Wall roughness").set_scalar(static_cast<float>(pipe.wall_roughness));
    connections_pending.push_back({wanda_pipe, pipe.from_node_id, 1});
    connections_pending.push_back({wanda_pipe, pipe.to_node_id, 2});
}

void WandaModelBuilder::finalize() {
    for (auto& connection : connections_pending) {
        try {
            model_.get_node(connection.node_id);
        }
         catch (const std::exception& e) {
            throw std::runtime_error("Node with id " + connection.node_id + " not found in model. Error: " + e.what());
        }
        model_.connect(connection.pipe_id, connection.connection_point, model_.get_node(connection.node_id));
    }
    model_.save_model_input();
    model_.close();
}



