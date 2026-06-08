#include "wanda_model_builder.h"
#include <string>
#include <numeric>
#include <numbers>

constexpr const char *WANDABIN = R"(c:\Program Files (x86)\Deltares\Wanda 4.8\Bin64\)";

WandaModelBuilder::WandaModelBuilder(const std::string &wanda_file,
                                     const CoordinatesConverter &converter) : model_(wanda_file, WANDABIN),
                                                                              converter_(converter) {
}

void WandaModelBuilder::add_node(const Node &node) {
    auto &wanda_node = model_.add_node("Hydraulic node", converter_.convert(node.position), node.id);
    wanda_node.get_property("Elevation").set_scalar(static_cast<float>(node.elevation));
    if (node.base_demand != 0) {
        auto &tap = model_.add_component("Tap non-return flow DP reopen", converter_.convert(node.position), node.id);
        tap.get_property("Initial delivery rate").set_scalar(static_cast<float>(node.base_demand));
        tap.get_property("Downstream pressure").set_scalar(0.0f);
        tap.get_property("Delta P for reopen").set_scalar(1000.0f);
        connections_pending.push_back({tap, node.id, 1});
    }
}

void WandaModelBuilder::add_pipe(const Pipe &pipe) {
    auto sum = std::accumulate(pipe.position.begin(), pipe.position.end(), DiagramCoordinates{0.0, 0.0},
                               [](DiagramCoordinates acc, const DiagramCoordinates& pos) {
                                   return DiagramCoordinates{acc.x + pos.x, acc.y + pos.y};
                               });
    auto n = static_cast<double>(pipe.position.size());
    std::vector<float> position = converter_.convert({sum.x / n, sum.y / n});
    // Angle of the pipe (horizontal = 0 rad), based on first and last vertices.
    const auto &start = pipe.position.front();
    const auto &end = pipe.position.back();
    double angle = std::atan2(end.y - start.y, end.x - start.x);

    auto &wanda_pipe = model_.add_component("Pipe (Liquid)", position, pipe.name);
    wanda_pipe.set_angle(static_cast<float>(angle));
    wanda_pipe.get_property("Length").set_scalar(static_cast<float>(pipe.length));
    wanda_pipe.get_property("Inner diameter").set_scalar(static_cast<float>(pipe.inner_diameter));
    wanda_pipe.get_property("Wall roughness").set_scalar(static_cast<float>(pipe.friction_model_roughness));
    connections_pending.push_back({wanda_pipe, pipe.from_node_id, 1});
    connections_pending.push_back({wanda_pipe, pipe.to_node_id, 2});
}

void WandaModelBuilder::add_reservoir(const Reservoir &reservoir) {
    auto &wanda_reservoir = model_.add_component("BoundH (reservoir)",
                                                 converter_.convert(reservoir.position), reservoir.name);
    wanda_reservoir.get_property("Head at t = 0 [s]").set_scalar(static_cast<float>(reservoir.head));
    connections_pending.push_back({wanda_reservoir, reservoir.name, 1});
}

void WandaModelBuilder::finalize() {
    for (auto &connection: connections_pending) {
        try {
            auto &node = model_.get_node(node_prefix + " " + connection.node_id);
            model_.connect(connection.pipe_id, connection.connection_point, node);
        } catch (const std::exception &e) {
            throw std::runtime_error("Node with id " + connection.node_id + " not found in model. Error: " + e.what());
        }
    }
    model_.save_model_input();
    model_.close();
}




