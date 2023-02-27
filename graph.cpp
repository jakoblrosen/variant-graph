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
    if (!this->nodes->contains(size)) {
        createLayer(size);
    }
    this->nodes->at(size)->push_back(newNode);
    auto *masterBitset = new std::bitset<BITSET_SIZE>(*newNode->getBits());
    auto *blacklist = new std::unordered_set<node *>;

    // check layer above
    if (this->nodes->contains(size - 1)) {
        for (size_t i = 0; i < size; i++) {
            masterBitset->set(newNode->getVariants()->at(i), false);
            if (this->parentLookup->contains(*masterBitset)) {
                node *currentNode = this->parentLookup->at(*masterBitset);
                currentNode->addEdge(newNode);
                blacklist->insert(currentNode);
                blacklist->merge(std::unordered_set<node *>(*currentNode->getBlacklist()));
            }
            masterBitset->set(newNode->getVariants()->at(i), true);
        }
    }
    this->parentLookup->insert({*masterBitset, newNode});

    // now search other nodes for other maximum subsets
    for (auto it = this->layers->rbegin(); it != this->layers->rend(); it++) {
        size_t currLayer = *it;

        // skip the two layers we have already solved for
        if (currLayer == size - 1 or currLayer == size) {
            continue;
        }

        auto *nodesAtLayer = this->nodes->at(currLayer);
        size_t nodesSize = nodesAtLayer->size();
        for (size_t currNodeIndex = 0; currNodeIndex < nodesSize; currNodeIndex++) {
            node *currentNode = nodesAtLayer->at(currNodeIndex);
            if (!blacklist->contains(currentNode) and newNode->isSupersetOf(currentNode)) {
                newNode->addEdge(currentNode);
                blacklist->insert(currentNode);
                blacklist->merge(std::unordered_set<node *>(*currentNode->getBlacklist()));
            }
        }
    }
    newNode->setBlacklist(blacklist);
    delete masterBitset;
}

void graph::insertNodes(std::vector<node *> *newNodes) {
    std::sort(newNodes->begin(), newNodes->end(),
              [](node *a, node *b){ return a->getVariants()->size() < b->getVariants()->size(); });
    for (auto & newNode : *newNodes) {
        this->insertNode(newNode);
    }
}

void graph::createLayer(size_t size) {
    this->layers->push_back(size);
    this->nodes->insert({size, new std::vector<node *>});
}
