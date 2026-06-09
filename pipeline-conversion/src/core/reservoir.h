#ifndef PIPELINE_CONVERSION_RESERVOIR_H
#define PIPELINE_CONVERSION_RESERVOIR_H

#include "coordinates.h"
#include "typedef.h"
#include <string>
#include <vector>

struct Reservoir {
    ComponentId name;
    double head;
    DiagramCoordinates position;
};

#endif // PIPELINE_CONVERSION_RESERVOIR_H