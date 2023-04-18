//
// Created by Jakob Rosen on 2/1/23.
//

#ifndef VARIANT_GRAPH_NODE_H
#define VARIANT_GRAPH_NODE_H


#include <vector>
#include <bitset>
#include <set>

#define BITSET_SIZE 1024

class node {
    std::vector<int> *variants;
    std::vector<node *> *edges;
    std::bitset<BITSET_SIZE> *bits;
    std::set<node *> *blacklist;
public:
    node(std::vector<int> *variants);
    std::vector<int> *getVariants();
    std::vector<node *> *getEdges();
    std::bitset<BITSET_SIZE> *getBits();
    std::set<node *> *getBlacklist();
    void addEdge(node *target);
    void updateBlacklist(std::set<node *> *blacklist);
    bool isSubsetOf(node *target);
    bool isSupersetOf(node *target);
};


#endif //VARIANT_GRAPH_NODE_H
