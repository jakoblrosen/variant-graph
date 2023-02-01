//
// Created by Jakob Rosen on 2/1/23.
//

#ifndef FINAL_PROJECT_NODE_H
#define FINAL_PROJECT_NODE_H


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


#endif //FINAL_PROJECT_NODE_H
