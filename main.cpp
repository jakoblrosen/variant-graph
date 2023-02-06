#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "graph.h"

void usage() {
    std::cout << "Usage: ./variant_graph <input_file> <output_file>" << std::endl;
}

void readFile(std::vector<node *> *nodes, const std::string &filename) {
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        file.close();
        std::cout << "Attempting to read from a file that does not exist" << std::endl;
        std::cout << "Exiting..." << std::endl;
        exit(1);
    }

    int i = 0;
    while (file.good()) {
        std::string input;
        std::getline(file, input);
        if (input.empty()) {
            return;
        }
        std::istringstream stream(input);
        auto variants = new std::vector<int>;
        std::string numStr;
        int num;
        while (std::getline(stream, numStr, ',')) {
            if (std::istringstream(numStr) >> num) {
                variants->push_back(num);
            }
        }
        nodes->push_back(new node(variants));
        i++;
    }
    file.close();
}

void writeFile(graph *graph, const std::string &filename) {
    std::ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        file.close();
        std::cout << "Error while writing to file " << filename << std::endl;
        std::cout << "Exiting..." << std::endl;
        exit(1);
    }

    for (size_t layerNum = 0; layerNum < graph->getLayers()->size(); layerNum++) {
        size_t currLayer = graph->getLayers()->at(layerNum);
        std::vector<node *> *nodesAtLayer = graph->getNodes()->at(currLayer);
        for (auto currNode : *nodesAtLayer) {
            for (size_t edge = 0; edge < currNode->getEdges()->size(); edge++) {
                for (int nodeVariant : *currNode->getVariants()) {
                    file << nodeVariant;
                    if (nodeVariant != currNode->getVariants()->back()) {
                        file << ",";
                    }
                }
                file << "->";
                for (int edgeVariant : *currNode->getEdges()->at(edge)->getVariants()) {
                    file << edgeVariant;
                    if (edgeVariant != currNode->getEdges()->at(edge)->getVariants()->back()) {
                        file << ",";
                    }
                }
                file << std::endl;
            }
        }
    }
    file.close();
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        usage();
        return 0;
    }
    auto variantGraph = new graph;
    auto nodes = new std::vector<node *>;

    std::cout << "Reading graph from " << argv[1] << std::endl;
    readFile(nodes, argv[1]);

    // start timer
    std::chrono::time_point start = std::chrono::system_clock::now();

    std::cout << "Sorting input data..." << std::endl;
    std::sort(nodes->begin(), nodes->end(),
              [](node *a, node *b){ return a->getVariants()->size() < b->getVariants()->size(); });

    std::cout << "Starting graph assembly..." << std::endl;
    size_t size = nodes->size();
    for (size_t i = 0; i < size; i++) {
        variantGraph->insertNode(nodes->at(i));
    }

    // end timer
    std::chrono::time_point end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Graph assembled in " << elapsed.count() << " seconds" << std::endl;

    std::cout << "Writing graph to " << argv[2] << std::endl;
    writeFile(variantGraph, argv[2]);
    return 0;
}
