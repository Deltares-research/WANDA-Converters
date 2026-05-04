#ifndef PIPELINE_CONVERSION_MODEL_CONVERTER_H
#define PIPELINE_CONVERSION_MODEL_CONVERTER_H
#include <set>
#include <string>
#include <string_view>
#include "core/network.h"

/**
 * @brief Top-level converter that reads a pipeline model from one format and writes it to another.
 *
 * @details Loads a pipeline network from the given input file and model type,
 *          then exports it to the specified output file and model type.
 *
 * @param input_file       Path to the source model file.
 * @param input_model_type Type of the source model (e.g. "WANDA", "EPAnet", "GIS").
 *
 * Methods:
 * - convert(output_file, output_model_type): Exports the loaded network to the target format.
 *   @param output_file       Path to the destination model file.
 *   @param output_model_type Type of the target model (e.g. "WANDA", "EPAnet", "GIS").
 */
class ModelConverter {
    public:
        ModelConverter(std::string_view input_file, std::string_view input_model_type);
        void convert(std::string_view output_file, std::string_view output_model_type);
    private:
    const std::set<std::string> supported_model_types = {"EPAnet", "WANDA", "GIS"} ;
    Network network;
};


#endif //PIPELINE_CONVERSION_MODEL_CONVERTER_H