#include <iostream>
#include "graph.h"

void printGraph(graph *graph) {
    for (size_t layerNum = 0; layerNum < graph->getLayers()->size(); layerNum++) {
        size_t currLayer = graph->getLayers()->at(layerNum);
        std::vector<node *> *nodesAtLayer = graph->getNodes()->at(currLayer);
        for (auto currNode : *nodesAtLayer) {
            for (size_t edge = 0; edge < currNode->getEdges()->size(); edge++) {
                for (int nodeVariant : *currNode->getVariants()) {
                    std::cout << nodeVariant << ",";
                }
                std::cout << "->";
                for (int edgeVariant : *currNode->getEdges()->at(edge)->getVariants()) {
                    std::cout << edgeVariant << ",";
                }
                std::cout << std::endl;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    auto *graphA = new graph;
    graphA->insertNode(new node(new std::vector({2})));
    graphA->insertNode(new node(new std::vector({1, 2})));
    graphA->insertNode(new node(new std::vector({2, 3})));
    graphA->insertNode(new node(new std::vector({1, 2, 3})));
    graphA->insertNode(new node(new std::vector({1, 2, 3, 4})));
    graphA->insertNode(new node(new std::vector({1, 2, 3, 4, 5})));
    printGraph(graphA);
    return 0;
}
