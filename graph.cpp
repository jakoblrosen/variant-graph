//
// Created by Jakob Rosen on 2/1/23.
//

#include "graph.h"

graph::graph() {
    this->nodes = new std::unordered_map<size_t, std::vector<node *> *>;
    this->layers = new std::vector<size_t>;
    this->parentLookup = new std::unordered_map<std::bitset<BITSET_SIZE>, node *>;
}

std::unordered_map<size_t, std::vector<node *> *> *graph::getNodes() {
    return this->nodes;
}

std::vector<size_t> *graph::getLayers() {
    return this->layers;
}

/* this function assumes that data is inserted in order */
void graph::insertNode(node *newNode) {
    std::vector<int> *variantsVector = newNode->getVariants();
    size_t size = variantsVector->size();
    if (this->nodes->find(size) == this->nodes->end()) {
        createLayer(size);
    }
    this->nodes->at(size)->push_back(newNode);

    for (std::vector<size_t>::reverse_iterator iter = this->layers->rbegin(); iter != this->layers->rend(); iter++) {
        if (*iter >= size) {
            continue;
        }
        auto *nodesAtLayer = this->nodes->at(*iter);
        for (node *cmpNode : *nodesAtLayer) {
            auto *blacklist = newNode->getBlacklist();
            if (blacklist->find(cmpNode) == blacklist->end() and newNode->isSupersetOf(cmpNode)) {
                cmpNode->addEdge(newNode);
                auto *newBlacklist = this->blacklistUnion(newNode->getBlacklist(), cmpNode->getBlacklist());
                newNode->updateBlacklist(newBlacklist);
            }
        }
    }
}

void graph::insertNodes(std::vector<node *> *newNodes) {
    std::sort(newNodes->begin(), newNodes->end(),
              [](node *a, node *b){ return a->getVariants()->size() < b->getVariants()->size(); });
    size_t size = newNodes->size();
    for (node *newNode : *newNodes) {
        this->insertNode(newNode);
    }
}

void graph::createLayer(size_t size) {
    this->layers->push_back(size);
    this->nodes->insert({size, new std::vector<node *>});
}

std::set<node *> *graph::blacklistUnion(std::set<node *> *a, std::set<node *> *b) {
    auto *result = new std::set<node *>(*a);
    result->insert(b->begin(), b->end());
    return result;
}
