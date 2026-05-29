#include "utility.h"
#include <stdexcept>
#include <string>

DiagramCoordinates get_coordinates(const EN_Project ph, const int node_index) {
    double x = 0.0;
    double y = 0.0;
    int ret_val = EN_getcoord(ph, node_index, &x, &y);
    if (ret_val != 0) {
        throw std::runtime_error("Error in EN_getcoord() error code is " + std::to_string(ret_val));
    }
    return {x, y};
}

std::vector<DiagramCoordinates> get_vertex(const EN_Project ph, const int link_index) {
    int vertex_count = 0;
    int ret_val = EN_getvertexcount(ph, link_index, &vertex_count);
    if (ret_val != 0) {
        throw std::runtime_error("Error in EN_getvertexcount() error code is " + std::to_string(ret_val));
    }
    std::vector<DiagramCoordinates> vertices;
    vertices.reserve(vertex_count);
    for (int i = 1; i <= vertex_count; ++i) {
        double x = 0.0;
        double y = 0.0;

        ret_val = EN_getvertex(ph, link_index, i, &x, &y);
        if (ret_val != 0) {
            throw std::runtime_error("Error in EN_getvertex() error code is " + std::to_string(ret_val));
        }
        vertices.emplace_back(x, y);
    }
    return vertices;
}

std::vector<DiagramCoordinates> get_link_coordinates(EN_Project ph, int link_index) {

    int from_node_idx = 0;
    int to_node_idx   = 0;

    int ret_val = EN_getlinknodes(ph, link_index, &from_node_idx, &to_node_idx);
    if (ret_val != 0) {
        throw std::runtime_error("Error in EN_getlinknodes() error code is " + std::to_string(ret_val));
    }

    std::vector<DiagramCoordinates> geometry;
    geometry.push_back(get_coordinates(ph, from_node_idx));
    // ---- Vertices ----
    auto vertices = get_vertex(ph, link_index);
    geometry.insert(geometry.end(), vertices.begin(), vertices.end());
    // ---- End node ----
    geometry.push_back(get_coordinates(ph, to_node_idx));
    return geometry;
}

