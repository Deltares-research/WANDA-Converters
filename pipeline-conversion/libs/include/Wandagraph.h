#ifndef WANDAAPI_WANDAGRAPH_H
#define WANDAAPI_WANDAGRAPH_H

#include "CXXGraph/CXXGraph.hpp"
#include <string>
#include <vector>

#ifdef WANDAMODEL_EXPORT
#define WANDAMODEL_API __declspec(dllexport)
#else
#define WANDAMODEL_API __declspec(dllimport)
#endif

struct NodeData {
    explicit NodeData(std::string node_id):identifier(std::move(node_id)), node(identifier, "1"){};
    std::string identifier;
    std::vector<std::string> connected_edges;
    CXXGraph::Node<std::string> node;
};

struct EdgeData {
    EdgeData(std::string edge_id, const NodeData& from_node_in, const NodeData& to_node_in, double length_in):
    identifier(std::move(edge_id)), from_node(from_node_in.identifier), to_node(to_node_in.identifier), edge(edge_id, from_node_in.node, to_node_in.node, length_in), length(length_in) {};
    std::string identifier;
    std::string from_node;
    std::string to_node;
    CXXGraph::UndirectedWeightedEdge<std::string> edge;
    double length;
};

struct EdgeInput {
    std::string edge_id;
    std::string from_node_id;
    std::string to_node_id;
    double length;
};

class WANDAMODEL_API WandaGraph{
public:
    explicit WandaGraph(const std::vector<EdgeInput>& edges);
    ~WandaGraph() = default;
    /**
     * Finds the shortest path between two edges in the graph.
     *
     * This function calculates the shortest path between the start and end edge
     * provided as string identifiers. If the start and end edges are the same, it
     * directly returns a single-element path. If the edges are directly connected,
     * it directly returns a two-element path. Otherwise, it employs Dijkstra's algorithm
     * to compute the shortest path through the nodes connected to the edges.
     * Please note that the edges are returned not the nodes.
     *
     * An exception is thrown if either the start or end edge does not exist within the graph.
     *
     * @param start_edge_str The identifier of the starting edge.
     * @param end_edge_str The identifier of the destination edge.
     * @return A vector of string identifiers representing the edges in the shortest path.
     * @throws std::runtime_error If the start or end edge does not exist in the graph.
     */
    std::vector<std::string> find_shortest_path(const std::string& start_edge, const std::string& end_edge) const;

    /**
     *
     * @return true when no edges are in the graph otherwise false
     */
    bool is_empty() const;
private:
    void add_edge(const std::string& edge_id, const std::string& from_node_id, const std::string& to_node_id, double length);
    std::unordered_map<std::string, NodeData> m_nodes;
    std::unordered_map<std::string, EdgeData> m_edges;
    bool node_exists(const std::string& node_id) const;
    bool edge_exists(const std::string& edge_id) const;
    CXXGraph::T_EdgeSet<std::string> m_edge_set;
    CXXGraph::Graph<std::string> m_graph;

    /**
     * Method to find the shortest path between two nodes using the Dijkstra algorithm.
     *
     * @param start_node_id: start node for which to find the shorest path to the end node.
     * @param end_node_id: end node for which to find the shorest path to the start node.
     * @return
     */
    CXXGraph::DijkstraResult get_shortest_path_between_nodes(const std::string& start_node_id, const std::string& end_node_id) const;

    /**
     * Method to get the two nodes connected to the given edges which are closest together.
     *
     * This method finds the two nodes connected to the two input edges which are the closest together.
     * @param start_edge
     * @param end_edge
     * @return
     */
    std::pair<std::string, std::string> get_closest_nodes(const EdgeData& start_edge, const EdgeData& end_edge) const;

    /**
     * Constructs a path from a sequence of nodes using the specified start and end edges.
     *
     * This function builds a path representation by combining the node sequence provided
     * in conjunction with the given start and end edges. It ensures that the edges at
     * the start and end of the path are appropriately connected to the given start and
     * end edges, respectively. The intermediate nodes are used to derive a coherent path
     * through the graph. If the node sequence is empty or invalid, an exception is typically
     * thrown to signal an error in the input parameters.
     *
     * @param nodes A vector of node identifiers representing the intermediate nodes of the path.
     * @param start_edge The starting edge in the constructed path.
     * @param end_edge The ending edge in the constructed path.
     * @return A vector of string identifiers representing the resultant path through the edges.
     * @throws std::runtime_error If the node sequence is invalid or improperly formatted.
     */
    std::vector<std::string> build_path_from_nodes(const std::vector<std::string>& nodes,
                                                   const EdgeData& start_edge,
                                                   const EdgeData& end_edge) const;
    /**
     * Retrieves the edge connecting two nodes within the graph.
     *
     * This method locates and returns the edge that connects the specified start and end nodes.
     * If there are multiple edges between the nodes, the edge with the shortest length is selected.
     * An exception is thrown if either of the nodes does not exist in the graph, or if no edge is found.
     *
     * @param start_node The identifier of the starting node.
     * @param end_node The identifier of the destination node.
     * @return A reference to the EdgeData object representing the edge connecting the two nodes.
     * @throws std::runtime_error If either the start or end node does not exist in the graph.
     * @throws std::runtime_error If no edge exists between the specified nodes.
     */
    const EdgeData& get_edge_between_nodes(const std::string& start_node, const std::string& end_node) const;


    /**
     * Method to get the node with the given identifier. If it does not exists a new node will be created.
     * @param identifier  : identifier for the node which needs to be created or return if exists.
     * @return
     */
    NodeData& get_or_create_node(const std::string& identifier);
};

bool are_edges_connected(const EdgeData& edge_1, const EdgeData& edge_2);

#endif //WANDAAPI_WANDAGRAPH_H