#ifndef VERTEX_OF_GRAPH_H
#define VERTEX_OF_GRAPH_H

#include <unordered_map>
#include <string>
#include <list>

class VertexOfGraph {
public:
    std::list<VertexOfGraph *> edges;

    size_t id() const;

    bool key_exists(const std::string& key) const;

    int& operator[](const std::string &key);

    const int& operator[](const std::string &key) const;

    VertexOfGraph();

    ~VertexOfGraph();

private:
    size_t identifier;
    std::unordered_map<std::string, int> vertex_map;
    static size_t amount_of_vertices;
};


#endif//VERTEX_OF_GRAPH_H