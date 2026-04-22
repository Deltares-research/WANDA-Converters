#ifndef PIPELINE_CONVERSION_MODEL_CONVERTER_H
#define PIPELINE_CONVERSION_MODEL_CONVERTER_H
#include <set>
#include <string>
#include <string_view>
#include "core/network.h"

class ModelConverter {
    public:
        ModelConverter(std::string_view input_file, std::string_view input_model_type);
        void convert(std::string_view output_file, std::string_view output_model_type);
    private:
    const std::set<std::string> supported_model_types = {"EPAnet", "WANDA", "GIS"} ;
    Network network;
};


#endif //PIPELINE_CONVERSION_MODEL_CONVERTER_H