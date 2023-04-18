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

    auto *masterBitset = new std::bitset<BITSET_SIZE>;
    for (size_t i = 0; i < size; i++) {
        masterBitset->set(variantsVector->at(i), true);
    }
    auto *subsets = new std::vector<std::bitset<BITSET_SIZE> *>;
    // check layer above
    if (this->nodes->contains(size - 1)) {
        for (size_t i = 0; i < size; i++) {
            masterBitset->set(newNode->getVariants()->at(i), false);
            if (this->parentLookup->contains(*masterBitset)) {
                this->parentLookup->at(*masterBitset)->addEdge(newNode);
                subsets->push_back(new std::bitset<BITSET_SIZE>(*masterBitset));
            }
            masterBitset->set(newNode->getVariants()->at(i), true);
        }
    }
    this->parentLookup->insert({*masterBitset, newNode});

    // now search other nodes for other maximum subsets
    size_t layerCount = this->layers->size();
    for (size_t i = layerCount - 1; true; i--) {
        size_t currLayer = this->layers->at(i);
        if (currLayer == size - 1 or currLayer == size) {
            if (i == 0) {
                break;
            }
            continue;
        }
        auto *nodesAtLayer = this->nodes->at(currLayer);
        size_t nodesSize = nodesAtLayer->size();
        for (size_t currNodeIndex = 0; currNodeIndex < nodesSize; currNodeIndex++) {
            auto *currentBitset = new std::bitset<BITSET_SIZE>;
            node *currentNode = nodesAtLayer->at(currNodeIndex);
            size_t currentNodeVariantsSize = currentNode->getVariants()->size();
            for (size_t j = 0; j < currentNodeVariantsSize; j++) {
                currentBitset->set(currentNode->getVariants()->at(j), true);
            }
            // check if current node variants are subset of new node
            if (*currentBitset == (*currentBitset & *masterBitset)) {
                size_t subsetSize = subsets->size();
                bool unique = true;
                for (size_t currSubsetIndex = 0; currSubsetIndex < subsetSize; currSubsetIndex++) {
                    std::bitset<BITSET_SIZE> *currSubset = subsets->at(currSubsetIndex);
                    if (*currentBitset == (*currentBitset & *currSubset)) {
                        unique = false;
                        break;
                    }
                }
                if (unique) {
                    this->parentLookup->at(*currentBitset)->addEdge(newNode);
                    subsets->push_back(currentBitset);
                }
            }
            delete currentBitset;
        }
        if (i == 0) {
            break;
        }
    }
    delete subsets;
    delete masterBitset;
}

void graph::insertNodes(std::vector<node *> *newNodes) {
    std::sort(newNodes->begin(), newNodes->end(),
              [](node *a, node *b){ return a->getVariants()->size() < b->getVariants()->size(); });
    size_t size = newNodes->size();
    for (size_t i = 0; i < size; i++) {
        this->insertNode(newNodes->at(i));
    }
}

void graph::createLayer(size_t size) {
    this->layers->push_back(size);
    this->nodes->insert({size, new std::vector<node *>});
}
