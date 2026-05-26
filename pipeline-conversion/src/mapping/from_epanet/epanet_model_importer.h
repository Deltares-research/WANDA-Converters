#ifndef PIPELINE_CONVERSION_EPANET_MODEL_IMPORTER_H
#define PIPELINE_CONVERSION_EPANET_MODEL_IMPORTER_H
#include <string>
#include "core/network.h"
#include "epanet2_2.h"

class EpanetImporter {
    public:
    explicit EpanetImporter(const std::string &model_file);

    ~EpanetImporter();

    Network import() const;
    private:
    EN_Project epanet_project;
};


#endif //PIPELINE_CONVERSION_EPANET_MODEL_IMPORTER_H