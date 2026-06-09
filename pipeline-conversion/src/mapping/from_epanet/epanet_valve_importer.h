#ifndef PIPELINE_CONVERSION_EPANET_VALVE_IMPORTER_H
#define PIPELINE_CONVERSION_EPANET_VALVE_IMPORTER_H
#include "epanet2_2.h"
#include "epanet_unit_converter.h"
#include "core/valve.h"

class EpanetValveImporter {
public:
    EpanetValveImporter() = default;
    Valve import(EN_Project ph, int link_index, const EpanetUnitConverter& unit_converter) const;
};

#endif //PIPELINE_CONVERSION_EPANET_VALVE_IMPORTER_H
