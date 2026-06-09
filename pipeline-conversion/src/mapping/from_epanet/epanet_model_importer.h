#ifndef PIPELINE_CONVERSION_EPANET_MODEL_IMPORTER_H
#define PIPELINE_CONVERSION_EPANET_MODEL_IMPORTER_H
#include "core/network.h"
#include "epanet2_2.h"
#include <string>

/**
 * @brief Imports an EPAnet model file (.inp) and converts it into a generic
 * Network.
 *
 * @param model_file Path to the EPAnet input file.
 *
 * Methods:
 * - import(): Reads all pipes and nodes from the EPAnet project and returns a
 * Network.
 *   @return A Network object representing the full pipeline model.
 */
class EpanetImporter {
  public:
    explicit EpanetImporter(const std::string &model_file);

    ~EpanetImporter();

    Network import() const;

  private:
    EN_Project epanet_project;
};

#endif // PIPELINE_CONVERSION_EPANET_MODEL_IMPORTER_H