#ifndef PIPELINE_CONVERSION_EPANET_PIPE_IMPORTER_H
#define PIPELINE_CONVERSION_EPANET_PIPE_IMPORTER_H

#include "core/pipe.h"
#include "epanet2_2.h"
#include "epanet_unit_converter.h"

class EpanetPipeImporter {
public:
    EpanetPipeImporter() = default;
    Pipe import(EN_Project ph, int link_index, const EpanetUnitConverter& unit_converter) const;
};


#endif //PIPELINE_CONVERSION_EPANET_PIPE_IMPORTER_H