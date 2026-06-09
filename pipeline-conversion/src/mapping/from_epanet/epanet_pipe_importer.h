#ifndef PIPELINE_CONVERSION_EPANET_PIPE_IMPORTER_H
#define PIPELINE_CONVERSION_EPANET_PIPE_IMPORTER_H

#include "core/pipe.h"
#include "epanet2_2.h"
#include "epanet_unit_converter.h"

/**
 * @brief Imports a single pipe from an EPAnet project into the generic Pipe
 * representation.
 *
 * Methods:
 * - import(ph, link_index, unit_converter): Reads pipe properties from the
 * EPAnet project.
 *   @param ph             Handle to the EPAnet project.
 *   @param link_index     1-based index of the link in the EPAnet model.
 *   @param unit_converter Reference to the unit converter for EPAnet-to-SI
 * conversion.
 *   @return A Pipe object populated with the link's properties.
 */
class EpanetPipeImporter {
  public:
    EpanetPipeImporter() = default;
    Pipe import(EN_Project ph, int link_index, const EpanetUnitConverter &unit_converter) const;
};

#endif // PIPELINE_CONVERSION_EPANET_PIPE_IMPORTER_H