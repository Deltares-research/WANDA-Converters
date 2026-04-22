#ifndef PIPELINE_CONVERSION_WANDA_MODEL_IMPORTER_H
#define PIPELINE_CONVERSION_WANDA_MODEL_IMPORTER_H
#include "core/network.h"
#include "wandamodel.h"

class WandaModelImporter {
public:
    WandaModelImporter(std::string model_file, std::string wanda_bin);
    ~WandaModelImporter();
    Network import() ;
private:
    wanda_model wanda_model_in;
};


#endif //PIPELINE_CONVERSION_WANDA_MODEL_IMPORTER_H