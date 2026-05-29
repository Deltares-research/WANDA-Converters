#ifndef PIPELINE_CONVERSION_WANDA_MODEL_EXPORTER_H
#define PIPELINE_CONVERSION_WANDA_MODEL_EXPORTER_H
#include "core/network.h"
#include <string>

/**
 * @brief Exports a generic Network to a WANDA model file.
 *
 * Methods:
 * - convert(network, output_file): Writes all nodes and pipes to a new WANDA model.
 *   @param network     The Network to export.
 *   @param output_file Path to the output WANDA model file (.wdi).
 */
class WandaModelExporter {
public:
    void convert(const Network& network,
                 std::string_view output_file) const;

};

class CoordinatesConverter {
public:
    CoordinatesConverter(float y_factor_in, float x_factor_in, float y_shift_in, float x_shift_in);
    std::vector<float> convert(const DiagramCoordinates& coordinates) const;
private:
    float y_factor;
    float x_factor;
    float y_shift;
    float x_shift;
};


#endif //PIPELINE_CONVERSION_WANDA_MODEL_EXPORTER_H