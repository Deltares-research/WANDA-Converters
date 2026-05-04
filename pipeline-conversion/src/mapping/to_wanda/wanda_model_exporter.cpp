#include "wanda_model_exporter.h"

#include "wanda_model_builder.h"


void WandaModelExporter::convert(const Network &network, std::string_view output_file) const {
    WandaModelBuilder builder((output_file.data()));
    for (const auto& node : network.nodes) {
        builder.add_node(node);
    }
    for (const auto& pipe : network.pipes) {
        builder.add_pipe(pipe);
    }
    builder.finalize();
}
