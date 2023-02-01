//
// Created by Jakob Rosen on 2/1/23.
//

#ifndef FINAL_PROJECT_GRAPH_H
#define FINAL_PROJECT_GRAPH_H


#include <unordered_map>
#include <vector>
#include "node.h"

class graph {
    std::unordered_map<size_t, std::vector<node *> *> *nodes;
    std::vector<size_t> *layers;

    void createLayer(size_t);
public:
    graph();
    std::unordered_map<size_t, std::vector<node *> *> *getNodes();
    std::vector<size_t> *getLayers();
    void insertNode(node *node);
};


#endif //FINAL_PROJECT_GRAPH_H
