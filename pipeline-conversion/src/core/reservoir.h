#ifndef PIPELINE_CONVERSION_RESERVOIR_H
#define PIPELINE_CONVERSION_RESERVOIR_H

#include <string>
#include <vector>
#include "typedef.h"

struct Reservoir {
    ComponentId name;
    double head;
    std::vector<float> position;
};


#endif //PIPELINE_CONVERSION_RESERVOIR_H