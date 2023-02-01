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

void graph::insertNode(node *newNode) {
    size_t size = newNode->getVariants()->size();
    if (!this->nodes->contains(size)) {
        createLayer(size);
    }
    this->nodes->at(size)->push_back(newNode);
    if (this->nodes->contains(size - 1)) {
        std::vector<node *> *parents = this->nodes->at(size - 1);
        size_t parentSize = parents->size();
        for (size_t i = 0; i < parentSize; i++) {
            if (newNode->isRelative(parents->at(i))) {
                parents->at(i)->addEdge(newNode);
            }
        }
    }
    if (this->nodes->contains(size + 1)) {
        std::vector<node *> *children = this->nodes->at(size + 1);
        size_t childrenSize = children->size();
        for (size_t i = 0; i < childrenSize; i++) {
            if (newNode->isRelative(children->at(i))) {
                newNode->addEdge(children->at(i));
            }
        }
    }
}

void graph::createLayer(size_t size) {
    this->layers->push_back(size);
    this->nodes->insert({size, new std::vector<node *>});
}
