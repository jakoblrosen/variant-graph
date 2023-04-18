//
// Created by Jakob Rosen on 2/1/23.
//

#include "node.h"

node::node(std::vector<int> *variants) {
    this->variants = variants;
    this->edges = new std::vector<node *>;
    auto *bits = new std::bitset<BITSET_SIZE>;
    for (int i : *variants) {
        bits->set(i);
    }
    this->bits = bits;
    this->blacklist = new std::set<node *>;
    this->blacklist->insert(this);
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

std::set<node *> *node::getBlacklist() {
    return this->blacklist;
}

void node::addEdge(node *target) {
    this->edges->push_back(target);
}

void node::updateBlacklist(std::set<node *> *blacklist) {
    delete this->blacklist;
    this->blacklist = blacklist;
}

bool node::isSubsetOf(node *target) {
    return *this->bits == (*this->bits & *target->bits);
}

bool node::isSupersetOf(node *target) {
    return *target->bits == (*target->bits & *this->bits);
}
