#ifndef PIPELINE_CONVERSION_WANDA_MODEL_BUILDER_H
#define PIPELINE_CONVERSION_WANDA_MODEL_BUILDER_H
#include "wandamodel.h"
#include "core/node.h"
#include "core/pipe.h"
#include "core/typedef.h"

struct Connection {
    wanda_component& pipe_id;
    NodeId node_id;
    int connection_point;
};

class WandaModelBuilder {
    public:
        explicit WandaModelBuilder(const std::string &wanda_file);

        ~WandaModelBuilder() {
             model_.close();
        }

        void add_node(const Node& node);
        void add_pipe(const Pipe& pipe);
        void finalize();
    private:
        wanda_model model_;
    std::vector<Connection> connections_pending;

};


#endif //PIPELINE_CONVERSION_WANDA_MODEL_BUILDER_H