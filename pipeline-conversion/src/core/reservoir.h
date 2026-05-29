#ifndef PIPELINE_CONVERSION_RESERVOIR_H
#define PIPELINE_CONVERSION_RESERVOIR_H

#include <string>
#include <vector>
#include "typedef.h"
#include "coordinates.h"

struct Reservoir {
    ComponentId name;
    double head;
    DiagramCoordinates position;
};


#endif //PIPELINE_CONVERSION_RESERVOIR_H