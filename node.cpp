//
// Created by Jakob Rosen on 2/1/23.
//

#include "node.h"

node::node(std::vector<int> *variants) {
    this->variants = variants;
    this->edges = new std::vector<node *>;
    this->bits = new std::bitset<BITSET_SIZE>;
    for (int variant : *this->variants) {
        this->bits->set(variant, true);
    }
    this->blacklist = nullptr;
}

std::vector<int> *node::getVariants() {
    return this->variants;
}

std::vector<node *> *node::getEdges() {
    return this->edges;
}

std::bitset<BITSET_SIZE> *node::getBits() {
    return this->bits;
}

std::unordered_set<node *> *node::getBlacklist() {
    return this->blacklist;
}

void node::addEdge(node *target) {
    this->edges->push_back(target);
}

void node::setBlacklist(std::unordered_set<node *> *newBlacklist) {
    this->blacklist = newBlacklist;
}

bool node::isSubsetOf(node *subset) {
    return (*this->bits == (*this->bits & *subset->bits));
}

bool node::isSupersetOf(node *superset) {
    return (*superset->bits == (*superset->bits & *this->bits));
}
