//
// Created by Jakob Rosen on 2/1/23.
//

#ifndef VARIANT_GRAPH_NODE_H
#define VARIANT_GRAPH_NODE_H


#include <vector>
#include <bitset>
#include <unordered_set>

#define BITSET_SIZE 1024

class node {
    std::vector<int> *variants;
    std::vector<node *> *edges;
    std::bitset<BITSET_SIZE> *bits;
    std::unordered_set<node *> *blacklist;
public:
    explicit node(std::vector<int> *variants);
    std::vector<int> *getVariants();
    std::vector<node *> *getEdges();
    std::bitset<BITSET_SIZE> *getBits();
    std::unordered_set<node *> *getBlacklist();
    void addEdge(node *target);
    void setBlacklist(std::unordered_set<node *> *blacklist);
    bool isSubsetOf(node *subset);
    bool isSupersetOf(node *superset);
};


#endif //VARIANT_GRAPH_NODE_H