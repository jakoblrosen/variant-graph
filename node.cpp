//
// Created by Jakob Rosen on 2/1/23.
//

#include "node.h"

node::node() {
    this->variants = new std::vector<int>;
    this->edges = new std::vector<node *>;
}

node::node(std::vector<int> *variants) {
    this->variants = variants;
    this->edges = new std::vector<node *>;
}

std::vector<int> *node::getVariants() {
    return this->variants;
}

std::vector<node *> *node::getEdges() {
    return this->edges;
}

void node::addEdge(node *target) {
    this->edges->push_back(target);
}

bool node::isRelative(node *relative) {
    int dif = 0;
    size_t thisSize = this->variants->size();
    size_t relativeSize = relative->variants->size();
    size_t thisIndex = 0;
    size_t relativeIndex = 0;
    while (thisIndex < thisSize && relativeIndex < relativeSize) {
        int thisVariant = this->variants->at(thisIndex);
        int relativeVariant = relative->variants->at(relativeIndex);
        if (thisVariant == relativeVariant) {
            thisIndex++;
            relativeIndex++;
        } else if (thisVariant > relativeVariant) {
            relativeIndex++;
            dif++;
        } else {
            thisIndex++;
            dif++;
        }

        if (dif > 1) {
            return false;
        }
    }

    return true;
}
