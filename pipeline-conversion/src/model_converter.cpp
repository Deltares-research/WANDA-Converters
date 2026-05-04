#include "model_converter.h"
#include <filesystem>
#include <iostream>
#include "mapping/from_wanda/wanda_model_importer.h"
#include "mapping/to_wanda/wanda_model_exporter.h"

ModelConverter::ModelConverter(const std::string_view input_file, const std::string_view input_model_type) {
    //check if input file exists:
    if (!std::filesystem::exists(input_file)) {
        throw std::runtime_error("Input file does not exist: " + std::string(input_file));
    }
    if (!supported_model_types.contains(std::string(input_model_type))) {
        throw std::runtime_error("Unsupported input model type: " + std::string(input_model_type));
    }
    if (input_model_type == "EPAnet") {
        std::cout << "EPAnet" << std::endl;
        return;
    }
    if (input_model_type == "WANDA") {
        std::cout << "WANDA" << std::endl;
        WandaModelImporter importer(std::string(input_file), "c:\\Program Files (x86)\\Deltares\\Wanda 4.8\\Bin64\\");
        network = importer.import();
        return;
    }
    if (input_model_type == "GIS") {
        std::cout << "GIS" << std::endl;
        return;
    }
}

void ModelConverter::convert(std::string_view output_file, std::string_view output_model_type) {
    if (std::filesystem::exists(output_file)) {
        throw std::runtime_error("Output file exist cannot override: " + std::string(output_file));
    }
    if (output_model_type == "EPAnet") {
        std::cout << "EPAnet" << std::endl;
        return;
    }
    if (output_model_type == "WANDA") {
        std::cout << "WANDA" << std::endl;
        WandaModelExporter converter;
        converter.convert(network, output_file);
        return;
    }
    if (output_model_type == "GIS") {
        std::cout << "GIS" << std::endl;
        return;
    }
}