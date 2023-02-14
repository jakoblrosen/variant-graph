//
// Created by Jakob Rosen on 2/1/23.
//

#include "graph.h"

graph::graph() {
    this->nodes = new std::unordered_map<size_t, std::vector<node *> *>;
    this->layers = new std::vector<size_t>;
    this->buckets = new std::unordered_map<int, std::vector<node *> *>;
}

std::unordered_map<size_t, std::vector<node *> *> *graph::getNodes() {
    return this->nodes;
}

std::vector<size_t> *graph::getLayers() {
    return this->layers;
}

/* this function assumes that data is inserted in order */
void graph::insertNode(node *newNode) {
    newNode->setBits();
    auto *variants = newNode->getVariants();
    size_t size = variants->size();
    if (!this->nodes->contains(size)) {
        this->createLayer(size);
    }
    this->nodes->at(size)->push_back(newNode);

    auto *blacklist = new std::unordered_set<node *>;
    for (size_t i = 0; i < size; i++) {
        int variant = variants->at(i);
        if (this->buckets->contains(variant)) {
            std::vector<node *> *bucket = this->buckets->at(variant);
            for (auto it = bucket->rbegin(); it != bucket->rend(); it++) {
                node *currentNode = *it;
                if (!blacklist->contains(currentNode) and newNode->isSubsetOf(currentNode)) {
                    newNode->addEdge(currentNode);
                    blacklist->insert(currentNode);
                    blacklist->merge(std::unordered_set<node *>(*currentNode->getBlacklist()));
                }
            }
        } else {
            this->buckets->insert({variant, new std::vector<node *>});
        }
        this->buckets->at(variant)->push_back(newNode);
    }
    newNode->setBlacklist(blacklist);
}

void graph::insertNodes(std::vector<node *> *newNodes) {
    std::sort(newNodes->begin(), newNodes->end(),
              [](node *a, node *b){ return a->getVariants()->size() < b->getVariants()->size(); });
    for (auto it = newNodes->rbegin(); it != newNodes->rend(); it++) {
        this->insertNode(*it);
    }
}

void graph::createLayer(size_t size) {
    this->layers->push_back(size);
    this->nodes->insert({size, new std::vector<node *>});
}
