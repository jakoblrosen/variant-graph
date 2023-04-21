//
// Created by Jakob Rosen on 2/1/23.
//

#ifndef VARIANT_GRAPH_GRAPH_H
#define VARIANT_GRAPH_GRAPH_H


#include <unordered_map>
#include <vector>
#include <ranges>
#include <set>
#include "node.h"

class graph {
    std::unordered_map<size_t, std::vector<node *> *> *nodes;
    std::vector<size_t> *layers;
    
    void createLayer(size_t);
    std::set<node *> *blacklistUnion(std::set<node *> *a, std::set<node *> *b);

public:
    graph();
    std::unordered_map<size_t, std::vector<node *> *> *getNodes();
    std::vector<size_t> *getLayers();
    void insertNode(node *newNode);
    void insertNodes(std::vector<node *> *newNodes);
};


#endif //VARIANT_GRAPH_GRAPH_H
