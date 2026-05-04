#ifndef PIPELINE_CONVERSION_WANDA_NODE_IMPORTER_H
#define PIPELINE_CONVERSION_WANDA_NODE_IMPORTER_H
#include "wandanode.h"
#include "core/node.h"


/**
 * @brief Imports a single node from a WANDA model into the generic Node representation.
 *
 * Methods:
 * - import(wandanode): Reads node properties from a wanda_node and returns a Node.
 *   @param wandanode Reference to the WANDA node.
 *   @return A Node object populated with the node's properties (id, elevation, etc.).
 */
class WandaNodeImporter {
    public:
    WandaNodeImporter() = default;
    Node import(wanda_node& wandanode) const;
};


#endif //PIPELINE_CONVERSION_WANDA_NODE_IMPORTER_H