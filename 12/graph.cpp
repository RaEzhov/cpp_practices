#include "graph.h"
#include <queue>


void Graph::new_vertex() {
    auto new_vertex = new VertexOfGraph;
    vertices_map[new_vertex->id()] = new_vertex;
}
Graph::~Graph() {
    for (auto i:vertices_map) {
        delete i.second;
    }
}
void Graph::new_vertex(std::initializer_list<int> edges_list) {
    auto new_vertex = new VertexOfGraph;
    for (auto edge: edges_list) {
        auto vIter = vertices_map.find(edge);
        if (vIter != vertices_map.end()) {
            new_vertex->edges.push_back(vIter->second);
            vIter->second->edges.push_back(new_vertex);
            vertices_map[new_vertex->id()] = new_vertex;
        } else {
            exit(-1); // One or more vertices are not exist
        }
    }
}

std::ostream& operator<< (std::ostream &out, const Graph &this_graph) {
    std::string str;
    str.reserve(this_graph.size()*20);
    for (const auto i: this_graph.vertices_map) {
        str += "Vertex: " + std::to_string(i.first) + "\nEdges: ";
        for (auto j: i.second->edges) {
            str += std::to_string(j->id()) + " ";
        }
        str += "\n";
    }
    out << str;
    return out;
}

void Graph::check_vertices(std::unordered_map<int, VertexOfGraph*>::iterator first, std::unordered_map<int, VertexOfGraph*>::iterator second) const{
    if(first == second){
        exit(-1); // first == second
    }
    if (first == vertices_map.end() or second == vertices_map.end()){
        exit(-1); // first vertex or second vertex is not exists
    }
}


void Graph::new_edge(size_t first, size_t second) {
    std::pair<std::unordered_map<int, VertexOfGraph*>::iterator , std::unordered_map<int, VertexOfGraph*>::iterator> iterators;
    iterators.first = vertices_map.find(first);
    iterators.second = vertices_map.find(second);
    check_vertices(iterators.first, iterators.second);
    for (auto i: iterators.first->second->edges){
        if (second == i->id()){
            exit(-1); // edge already exists
        }
    }
    iterators.first->second->edges.push_back(iterators.second->second);
    iterators.second->second->edges.push_back(iterators.first->second);
}

void Graph::new_edge(std::initializer_list<std::pair<size_t, size_t>> init_list) {
    for(auto it: init_list){
        new_edge(it.first, it.second);
    }
}


size_t Graph::size() const {
    return vertices_map.size();
}

void Graph::delete_vertex(size_t id) {
    if (vertices_map.find(id) == vertices_map.end()){
        exit(-1); // there is no such vertex in the graph
    }
    for (auto edge:vertices_map[id]->edges){
        edge->edges.remove(vertices_map[id]);
    }
    delete vertices_map[id];
    vertices_map.erase(id);
}

void Graph::delete_edge(size_t first, size_t second) {
    std::pair<std::unordered_map<int, VertexOfGraph*>::iterator , std::unordered_map<int, VertexOfGraph*>::iterator> iterators;
    iterators.first = vertices_map.find(first);
    iterators.second = vertices_map.find(second);
    check_vertices(iterators.first, iterators.second);
    iterators.first->second->edges.remove(iterators.second->second);
    iterators.second->second->edges.remove(iterators.first->second);
}

VertexOfGraph &Graph::operator[](size_t id) {
    auto iter = vertices_map.find(id);
    if (iter == vertices_map.end()){
        exit(-1); // No this key in map
    }
    return *vertices_map[id];
}

void Graph::dfs_visit(VertexOfGraph *vertex, const std::function<void (const VertexOfGraph&)>& func,
                      std::unordered_map<VertexOfGraph*,vertex_color>& colors) const{
    colors[vertex] = GRAY;
    func(*vertex);
    for (auto v: vertex->edges){
        if(colors[v] == WHITE){
            dfs_visit(v, func, colors);
        }
    }
    colors[vertex] = BLACK;
}

void Graph::depth_first_search(const std::function<void (const VertexOfGraph&)>& func) const{
    std::unordered_map<VertexOfGraph*, vertex_color> colors;
    for (auto v: vertices_map){
        colors[v.second] = WHITE;
    }
    for(auto v: vertices_map){
        if(colors[v.second] == WHITE){
            dfs_visit(v.second, func, colors);
        }
    }
}

void Graph::breadth_first_search(const std::function<void (const VertexOfGraph&)>& func) const{
    std::unordered_map<VertexOfGraph*, vertex_color> colors;
    for (auto v: vertices_map){
        colors[v.second] = WHITE;
    }
    std::queue<VertexOfGraph*> q;
    q.push(vertices_map.begin()->second);
    while (!q.empty()){
        VertexOfGraph* u = q.front();
        q.pop();
        for (auto v: u->edges){
            if (colors[v] == WHITE) {
                colors[v] = GRAY;
                q.push(v);
            }
        }
        func(*u);
        colors[u] = BLACK;
    }
}