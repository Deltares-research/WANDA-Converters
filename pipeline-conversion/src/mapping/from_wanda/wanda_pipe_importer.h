#ifndef PIPELINE_CONVERSION_WANDA_PIPE_IMPORTER_H
#define PIPELINE_CONVERSION_WANDA_PIPE_IMPORTER_H
#include "core/pipe.h"
#include "wandacomponent.h"

class WandaPipeImporter {
    public:
    WandaPipeImporter() = default;
    Pipe import(wanda_component& wandacomponent) const;
};


#endif //PIPELINE_CONVERSION_WANDA_PIPE_IMPORTER_H