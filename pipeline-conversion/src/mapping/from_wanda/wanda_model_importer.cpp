#include "wanda_model_importer.h"

#include "wanda_node_importer.h"
#include "wanda_pipe_importer.h"

Network WandaModelImporter::import()  {
    Network network;
    //do all the conversion of pipes.
    WandaPipeImporter pipe_importer;
    for (auto& pipe : wanda_model_in.get_all_pipes()) {
      network.pipes.push_back(pipe_importer.import(*pipe));
    }
    WandaNodeImporter node_importer;
    for (auto& node : wanda_model_in.get_all_nodes()) {
        network.nodes.push_back(node_importer.import(*node));
    }
    return network;
}

WandaModelImporter::WandaModelImporter(const std::string& model_file, const std::string& wanda_bin):wanda_model_in(model_file, wanda_bin) {
}

WandaModelImporter::~WandaModelImporter() {
    wanda_model_in.close();
}
