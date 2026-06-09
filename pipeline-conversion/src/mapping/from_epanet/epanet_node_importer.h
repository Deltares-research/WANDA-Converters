#ifndef PIPELINE_CONVERSION_EPANET_NODE_IMPORTER_H
#define PIPELINE_CONVERSION_EPANET_NODE_IMPORTER_H

#include "core/node.h"
#include "epanet2_2.h"
#include "epanet_unit_converter.h"

/**
 * @brief Imports a single node from an EPAnet project into the generic Node
 * representation.
 *
 * Methods:
 * - import(ph, node_index, unit_converter): Reads node properties from the
 * EPAnet project.
 *   @param ph             Handle to the EPAnet project.
 *   @param node_index     1-based index of the node in the EPAnet model.
 *   @param unit_converter Reference to the unit converter for EPAnet-to-SI
 * conversion.
 *   @return A Node object populated with the node's properties.
 */
class EpanetNodeImporter {
  public:
    EpanetNodeImporter() = default;
    Node import(EN_Project ph, int node_index, const EpanetUnitConverter &unit_converter) const;
};

#endif // PIPELINE_CONVERSION_EPANET_NODE_IMPORTER_H
