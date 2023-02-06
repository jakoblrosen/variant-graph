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

    auto *variantsBitset = new std::bitset<BITSET_SIZE>;
    for (size_t i = 0; i < size; i++) {
        variantsBitset->set(variantsVector->at(i), true);
    }
    for (size_t i = 0; i < size; i++) {
        variantsBitset->set(variantsVector->at(i), false);
        if (parentLookup->contains(*variantsBitset)) {
            node *parent = parentLookup->at(*variantsBitset);
            parent->addEdge(newNode);
        }
        variantsBitset->set(variantsVector->at(i), true);
    }
    this->parentLookup->insert({*variantsBitset, newNode});
}

void graph::createLayer(size_t size) {
    this->layers->push_back(size);
    this->nodes->insert({size, new std::vector<node *>});
}
