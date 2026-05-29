#include "wanda_model_exporter.h"

#include "wanda_model_builder.h"
#include <algorithm>
#include <vector>


void WandaModelExporter::convert(const Network &network, std::string_view output_file) const {

    std::vector<DiagramCoordinates> all_coordinates;
    std::transform(network.nodes.begin(), network.nodes.end(), std::back_inserter(all_coordinates),
                   [](const auto& node) { return node.position; });
    std::transform(network.reservoirs.begin(), network.reservoirs.end(), std::back_inserter(all_coordinates),
                   [](const auto& reservoir) { return reservoir.position; });
    for (const auto& pipe : network.pipes) {
        all_coordinates.insert(all_coordinates.end(), pipe.position.begin(), pipe.position.end());
    }

    auto [x_min, x_max] = std::minmax_element(all_coordinates.begin(), all_coordinates.end(),
                                                [](const auto& a, const auto& b) { return a.x < b.x; });
    auto [y_min, y_max] = std::minmax_element(all_coordinates.begin(), all_coordinates.end(),
                                                [](const auto& a, const auto& b) { return a.y < b.y; });
    float y_factor = 100 / y_max->y;
    float x_factor = 100 / x_max->x;
    float y_shift = -y_max->y * y_factor - 10;
    CoordinatesConverter coord_converter(y_factor, x_factor, y_shift, 0.0f);
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
