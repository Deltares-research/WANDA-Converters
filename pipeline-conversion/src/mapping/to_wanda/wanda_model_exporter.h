
#ifndef PIPELINE_CONVERSION_WANDA_MODEL_EXPORTER_H
#define PIPELINE_CONVERSION_WANDA_MODEL_EXPORTER_H
#include "core/network.h"
#include <string>

class WandaModelExporter {
public:
    void convert(const Network& network,
                 std::string_view output_file) const;

};


#endif //PIPELINE_CONVERSION_WANDA_MODEL_EXPORTER_H