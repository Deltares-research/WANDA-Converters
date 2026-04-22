#ifndef PIPELINE_CONVERSION_WANDA_NODE_IMPORTER_H
#define PIPELINE_CONVERSION_WANDA_NODE_IMPORTER_H
#include "wandanode.h"
#include "core/node.h"


class WandaNodeImporter {
    public:
    WandaNodeImporter() = default;
    Node import(wanda_node& wandanode) const;
};


#endif //PIPELINE_CONVERSION_WANDA_NODE_IMPORTER_H