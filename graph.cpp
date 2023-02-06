//
// Created by Jakob Rosen on 2/1/23.
//

#include "graph.h"

graph::graph() {
    this->nodes = new std::unordered_map<size_t, std::vector<node *> *>;
    this->layers = new std::vector<size_t>;
}

std::unordered_map<size_t, std::vector<node *> *> *graph::getNodes() {
    return this->nodes;
}

std::vector<size_t> *graph::getLayers() {
    return this->layers;
}

/* this function assumes that data is inserted in order */
void graph::insertNode(node *newNode) {
    size_t size = newNode->getVariants()->size();
    if (!this->nodes->contains(size)) {
        createLayer(size);
    }
    this->nodes->at(size)->push_back(newNode);
    if (this->nodes->contains(size - 1)) {
        std::vector<node *> *parents = this->nodes->at(size - 1);
        size_t parentSize = parents->size();
        bool related[parentSize];
        #pragma omp parallel for shared(newNode, parents, parentSize, related) default(none)
        for (size_t i = 0; i < parentSize; i++) {
            related[i] = newNode->isRelative(parents->at(i));
        }
        for (size_t i = 0; i < parentSize; i++) {
            if (related[i]) {
                parents->at(i)->addEdge(newNode);
            }
        }
    }
}

void graph::createLayer(size_t size) {
    this->layers->push_back(size);
    this->nodes->insert({size, new std::vector<node *>});
}
