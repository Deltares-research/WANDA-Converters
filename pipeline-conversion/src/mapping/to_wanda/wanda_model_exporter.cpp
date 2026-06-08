#include "wanda_model_exporter.h"

#include "wanda_model_builder.h"
#include <algorithm>
#include <cmath>
#include <vector>

namespace {
    // Typical on-diagram size of a Wanda component (in Wanda diagram units).
    // The scale is chosen so that the median distance between connected
    // components maps to roughly this value, keeping components from
    // overlapping while keeping the diagram compact.
    constexpr float WANDA_COMPONENT_SIZE = 100.0f;
    // Margin (in Wanda diagram units) around the diagram.
    constexpr float DIAGRAM_MARGIN = 10.0f;
    // Distance the top of the diagram is pushed below y = 0 so that every
    // component ends up at a negative y coordinate (Wanda convention here).
    constexpr float Y_OFFSET_BELOW_ZERO = 100.0f;

    // Median straight-line length of the pipes (start vertex to end vertex).
    // Falls back to the bounding-box diagonal when no usable pipes exist.
    float characteristic_distance(const Network &network,
                                  const DiagramCoordinates &min,
                                  const DiagramCoordinates &max) {
        std::vector<float> lengths;
        lengths.reserve(network.pipes.size());
        for (const auto &pipe : network.pipes) {
            if (pipe.position.size() < 2) continue;
            const auto &a = pipe.position.front();
            const auto &b = pipe.position.back();
            const double dx = b.x - a.x;
            const double dy = b.y - a.y;
            const float len = static_cast<float>(std::hypot(dx, dy));
            if (len > 0.0f) lengths.push_back(len);
        }
        if (!lengths.empty()) {
            const auto mid = lengths.begin() + lengths.size() / 2;
            std::nth_element(lengths.begin(), mid, lengths.end());
            return *mid;
        }
        const double dx = max.x - min.x;
        const double dy = max.y - min.y;
        const float diag = static_cast<float>(std::hypot(dx, dy));
        return diag > 0.0f ? diag : 1.0f;
    }
}

void WandaModelExporter::convert(const Network &network, std::string_view output_file) const {

    std::vector<DiagramCoordinates> all_coordinates;
    std::transform(network.nodes.begin(), network.nodes.end(), std::back_inserter(all_coordinates),
                   [](const auto& node) { return node.position; });
    std::transform(network.reservoirs.begin(), network.reservoirs.end(), std::back_inserter(all_coordinates),
                   [](const auto& reservoir) { return reservoir.position; });
    for (const auto& pipe : network.pipes) {
        all_coordinates.insert(all_coordinates.end(), pipe.position.begin(), pipe.position.end());
    }

    auto [x_min_it, x_max_it] = std::minmax_element(all_coordinates.begin(), all_coordinates.end(),
                                                [](const auto& a, const auto& b) { return a.x < b.x; });
    auto [y_min_it, y_max_it] = std::minmax_element(all_coordinates.begin(), all_coordinates.end(),
                                                [](const auto& a, const auto& b) { return a.y < b.y; });
    const DiagramCoordinates min{x_min_it->x, y_min_it->y};
    const DiagramCoordinates max{x_max_it->x, y_max_it->y};

    // Uniform scale: one "typical pipe length" -> WANDA_COMPONENT_SIZE units.
    // Y is NOT flipped (that would mirror the network); instead the diagram is
    // shifted downwards so every component lies below y = 0, with a margin.
    const float scale = WANDA_COMPONENT_SIZE / characteristic_distance(network, min, max);
    const float x_factor = scale;
    const float y_factor = scale;

    const float x_shift = DIAGRAM_MARGIN - static_cast<float>(min.x) * x_factor;
    const float y_shift = -Y_OFFSET_BELOW_ZERO - static_cast<float>(max.y) * y_factor;

    CoordinatesConverter coord_converter(y_factor, x_factor, y_shift, x_shift);
    WandaModelBuilder builder((output_file.data()), coord_converter);
    for (const auto& node : network.nodes) {
        builder.add_node(node);
    }
    for (const auto& pipe : network.pipes) {
        builder.add_pipe(pipe);
    }
    for (const auto& reservoir : network.reservoirs) {
        builder.add_reservoir(reservoir);
    }
    builder.finalize();
}

CoordinatesConverter::CoordinatesConverter(float y_factor_in, float x_factor_in, float y_shift_in, float x_shift_in):
y_factor(y_factor_in), x_factor(x_factor_in), y_shift(y_shift_in), x_shift(x_shift_in) {
}

std::vector<float> CoordinatesConverter::convert(const DiagramCoordinates &coordinates) const {
    float x = static_cast<float>(coordinates.x) * x_factor + x_shift;
    float y = static_cast<float>(coordinates.y) * y_factor + y_shift;
    return {x,y};
}
