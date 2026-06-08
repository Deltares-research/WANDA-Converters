#ifndef PIPELINE_CONVERSION_WANDA_MODEL_BUILDER_H
#define PIPELINE_CONVERSION_WANDA_MODEL_BUILDER_H
#include "wandamodel.h"
#include "wanda_model_exporter.h"
#include "core/node.h"
#include "core/pipe.h"
#include "core/reservoir.h"
#include "core/typedef.h"

/**
 * @brief Represents a pending connection between a pipe and a node in the WANDA model.
 *
 * Fields:
 * - pipe_id           : Reference to the WANDA pipe component.
 * - node_id           : Identifier of the node to connect.
 * - connection_point  : Connection point index on the pipe (1 = upstream, 2 = downstream).
 */
struct Connection {
    wanda_component& pipe_id;
    NodeId node_id;
    int connection_point;
};

/**
 * @brief Builds a WANDA model by adding nodes and pipes, then finalizing connections.
 *
 * @param wanda_file Path to the WANDA output file to create.
 *
 * Methods:
 * - add_node(node): Adds a hydraulic node to the WANDA model.
 * - add_pipe(pipe): Adds a pipe component and queues its connections.
 * - finalize():     Connects all pipes to their respective nodes and saves the model.
 */
class WandaModelBuilder {
    public:
        explicit WandaModelBuilder(const std::string &wanda_file, const CoordinatesConverter& converter);

        ~WandaModelBuilder() {
             model_.close();
        }

        void add_node(const Node& node);
        void add_pipe(const Pipe& pipe);
        void add_reservoir(const Reservoir& reservoir);
        void add_valve(const Valve& valve);
        void finalize();
    private:
        wanda_model model_;
    CoordinatesConverter converter_;
    std::vector<Connection> connections_pending;
    const std::string node_prefix = "H-node";

};



#endif //PIPELINE_CONVERSION_WANDA_MODEL_BUILDER_H