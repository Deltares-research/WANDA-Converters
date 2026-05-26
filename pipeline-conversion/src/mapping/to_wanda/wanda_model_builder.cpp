#include "wanda_model_builder.h"
#include <string>

constexpr const char* WANDABIN = R"(c:\Program Files (x86)\Deltares\Wanda 4.8\Bin64\)";

WandaModelBuilder::WandaModelBuilder(const std::string &wanda_file): model_(wanda_file, WANDABIN) {
}

void WandaModelBuilder::add_node(const Node &node) {

    auto& wanda_node = model_.add_node("Hydraulic node",{0,0}, node.id);
    wanda_node.get_property("Elevation").set_scalar(static_cast<float>(node.elevation));
}

void WandaModelBuilder::add_pipe(const Pipe &pipe) {
    auto& wanda_pipe = model_.add_component("Pipe (Liquid)",pipe.position, pipe.name);
    wanda_pipe.get_property("Length").set_scalar(static_cast<float>(pipe.length));
    wanda_pipe.get_property("Inner diameter").set_scalar(static_cast<float>(pipe.inner_diameter));
    wanda_pipe.get_property("Wall roughness").set_scalar(static_cast<float>(pipe.friction_model_roughness));
    connections_pending.push_back({wanda_pipe, pipe.from_node_id, 1});
    connections_pending.push_back({wanda_pipe, pipe.to_node_id, 2});
}

void WandaModelBuilder::add_reservoir(const Reservoir &reservoir) {
    auto& wanda_reservoir = model_.add_component("BoundH (reservoir)", reservoir.position, reservoir.name);
    wanda_reservoir.get_property("Head at t = 0 [s]").set_scalar(static_cast<float>(reservoir.head));
    connections_pending.push_back({wanda_reservoir, reservoir.name, 1});
}

void WandaModelBuilder::finalize() {
    for (auto& connection : connections_pending) {
        try {
            auto& node = model_.get_node(node_prefix + " " + connection.node_id);
            model_.connect(connection.pipe_id, connection.connection_point, node);
        }
         catch (const std::exception& e) {
            throw std::runtime_error("Node with id " + connection.node_id + " not found in model. Error: " + e.what());
        }

    }
    model_.save_model_input();
    model_.close();
}



