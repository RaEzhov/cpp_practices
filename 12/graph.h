#ifndef GRAPH_H
#define GRAPH_H
#include "vertex_of_graph.h"
#include <functional>

enum vertex_color{WHITE, GRAY, BLACK};

class Graph {
public:
    void new_vertex();

    void new_vertex(std::initializer_list<int> edges_list);

    void new_edge(size_t first, size_t second);

    void new_edge(std::initializer_list<std::pair<size_t, size_t>> init_list);

    void delete_vertex(size_t id);

    void delete_edge(size_t first, size_t second);

    size_t size() const;

    friend std::ostream &operator<<(std::ostream &out, const Graph &this_graph);

    VertexOfGraph& operator[](size_t id);

    void depth_first_search(const std::function<void (const VertexOfGraph&)>& func) const;

    void breadth_first_search(const std::function<void (const VertexOfGraph&)>& func) const;

    ~Graph();

private:
    std::unordered_map<int, VertexOfGraph *> vertices_map;

    void check_vertices(std::unordered_map<int, VertexOfGraph*>::iterator, std::unordered_map<int, VertexOfGraph*>::iterator) const;

    void dfs_visit(VertexOfGraph* vertex,const std::function<void (const VertexOfGraph&)>& func, std::unordered_map<VertexOfGraph*,vertex_color>& colors) const;
};

#endif//GRAPH_H