//
// Created by Jakob Rosen on 2/1/23.
//

#ifndef VARIANT_GRAPH_NODE_H
#define VARIANT_GRAPH_NODE_H


#include <vector>

class node {
    std::vector<int> *variants;
    std::vector<node *> *edges;
public:
    node();
    explicit node(std::vector<int> *variants);
    std::vector<int> *getVariants();
    std::vector<node *> *getEdges();
    void addEdge(node *target);
    bool isRelative(node *relative);
};


#endif //VARIANT_GRAPH_NODE_H
