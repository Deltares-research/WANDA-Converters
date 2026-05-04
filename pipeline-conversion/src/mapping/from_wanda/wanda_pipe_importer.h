#ifndef PIPELINE_CONVERSION_WANDA_PIPE_IMPORTER_H
#define PIPELINE_CONVERSION_WANDA_PIPE_IMPORTER_H
#include "core/pipe.h"
#include "wandacomponent.h"

/**
 * @brief Imports a single pipe from a WANDA model component into the generic Pipe representation.
 *
 * Methods:
 * - import(wandacomponent): Reads pipe properties from a wanda_component and returns a Pipe.
 *   @param wandacomponent Reference to the WANDA component describing the pipe.
 *   @return A Pipe object populated with the component's properties.
 */
class WandaPipeImporter {
    public:
    WandaPipeImporter() = default;
    Pipe import(wanda_component& wandacomponent) const;
};


#endif //PIPELINE_CONVERSION_WANDA_PIPE_IMPORTER_H