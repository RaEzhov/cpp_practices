#include "vertex_of_graph.h"
VertexOfGraph::VertexOfGraph(){
    identifier = amount_of_vertices;
    amount_of_vertices++;
}
VertexOfGraph::~VertexOfGraph() {
    amount_of_vertices--;
}
size_t VertexOfGraph::id() const {
    return identifier;
}

size_t VertexOfGraph::amount_of_vertices = 0;

const int& VertexOfGraph::operator[](const std::string &key) const{
    auto res = vertex_map.find(key);
    if (res == vertex_map.end()){
        exit(-1); // No this key
    }
    return res->second;
}

bool VertexOfGraph::key_exists(const std::string& key) const{
    auto it = vertex_map.find(key);
    return it != vertex_map.end();
}

int &VertexOfGraph::operator[](const std::string &key) {
    return vertex_map[key];
}
