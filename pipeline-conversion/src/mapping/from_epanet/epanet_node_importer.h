#ifndef PIPELINE_CONVERSION_EPANET_NODE_IMPORTER_H
#define PIPELINE_CONVERSION_EPANET_NODE_IMPORTER_H

#include "core/node.h"
#include "epanet2_2.h"
#include "epanet_unit_converter.h"

class EpanetNodeImporter {
public:
    EpanetNodeImporter() = default;
    Node import(EN_Project ph, int node_index, const EpanetUnitConverter& unit_converter) const;
};

#endif //PIPELINE_CONVERSION_EPANET_NODE_IMPORTER_H

