#include <iostream>
#include "graph.h"

int main() {
    Graph my_graph;
    for (int i = 0; i < 11; i++) {
        my_graph.new_vertex();
    }
    my_graph.new_edge({{10, 9},
                       {9,  8},
                       {8,  7},
                       {7,  2},
                       {9,  6},
                       {6,  3},
                       {3,  1},
                       {9,  5},
                       {5,  4}
                      });
    my_graph[10]["my_key"] = 456789;
    my_graph[8]["my_key"] = 123;
    my_graph[6]["my_key"] = 456;
    my_graph[2]["my_key"] = 90;
    my_graph[1]["my_key"] = 1;
    my_graph.delete_vertex(0);
    my_graph.breadth_first_search([](const VertexOfGraph &v) {
        std::string key = "my_key";
        if (v.key_exists(key)) {
            std::cout << "Vertex: " << v.id() << ", value: " << v[key] << '\n';
        }
    });
    return 0;
}