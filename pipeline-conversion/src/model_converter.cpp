#include "model_converter.h"
#include <filesystem>
#include <iostream>
#include "mapping/from_wanda/wanda_model_importer.h"

ModelConverter::ModelConverter(const std::string_view input_file, const std::string_view input_model_type) {
    //check if input file exists:
    if (!std::filesystem::exists(input_file)) {
        throw std::runtime_error("Input file does not exist: " + std::string(input_file));
    }
    if (supported_model_types.find(std::string(input_model_type)) == supported_model_types.end()) {
        throw std::runtime_error("Unsupported input model type: " + std::string(input_model_type));
    }
    if (input_model_type == "EPAnet") {
        std::cout << "EPAnet" << std::endl;
    }
    if (input_model_type == "WANDA") {
        std::cout << "WANDA" << std::endl;
        WandaModelImporter importer(std::string(input_file), "c:\\Program Files (x86)\\Deltares\\Wanda 4.8\\Bin64\\");
        importer.import();
    }
    if (input_model_type == "GIS") {
        std::cout << "GIS" << std::endl;
    }
}

void ModelConverter::convert(std::string_view output_file, std::string_view output_model_type) {}