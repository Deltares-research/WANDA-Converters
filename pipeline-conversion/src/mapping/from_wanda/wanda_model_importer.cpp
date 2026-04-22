#include "wanda_model_importer.h"
#include "wanda_pipe_importer.h"

Network WandaModelImporter::import()  {
    Network network;
    //do all the conversion of pipes.
    WandaPipeImporter importer;
    for (auto& pipe : wanda_model_in.get_all_pipes()) {
        auto pipe_local = importer.import(*pipe);
    }
    return network;
}

WandaModelImporter::WandaModelImporter(std::string model_file, std::string wanda_bin):wanda_model_in(model_file, wanda_bin) {
}

WandaModelImporter::~WandaModelImporter() {
    wanda_model_in.close();
}
