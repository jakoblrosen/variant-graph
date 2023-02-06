//
// Created by Jakob Rosen on 2/1/23.
//

#ifndef VARIANT_GRAPH_GRAPH_H
#define VARIANT_GRAPH_GRAPH_H


#include <unordered_map>
#include <vector>
#include <bitset>
#include "node.h"

#define BITSET_SIZE 1024

class graph {
    std::unordered_map<size_t, std::vector<node *> *> *nodes;
    std::vector<size_t> *layers;
    std::unordered_map<std::bitset<BITSET_SIZE>, node *> *parentLookup;

    void createLayer(size_t);
public:
    graph();
    std::unordered_map<size_t, std::vector<node *> *> *getNodes();
    std::vector<size_t> *getLayers();
    void insertNode(node *node);
};


#endif //VARIANT_GRAPH_GRAPH_H
