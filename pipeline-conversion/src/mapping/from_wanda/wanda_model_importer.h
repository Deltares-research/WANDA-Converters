#ifndef PIPELINE_CONVERSION_WANDA_MODEL_IMPORTER_H
#define PIPELINE_CONVERSION_WANDA_MODEL_IMPORTER_H
#include "core/network.h"
#include "wandamodel.h"

/**
 * @brief Imports an entire WANDA model file and converts it into a generic Network.
 *
 * @param model_file Path to the WANDA model file (.wdi).
 * @param wanda_bin  Path to the WANDA binaries directory.
 *
 * Methods:
 * - import(): Loads the WANDA model and returns a Network containing all nodes and pipes.
 *   @return A Network object representing the full pipeline model.
 */
class WandaModelImporter {
public:
    WandaModelImporter(const std::string &model_file, const std::string &wanda_bin);

    ~WandaModelImporter();

    Network import();

private:
    wanda_model wanda_model_in;
};


#endif //PIPELINE_CONVERSION_WANDA_MODEL_IMPORTER_H
