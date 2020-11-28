#pragma once

#include <unordered_map>
#include <list>
#include <string>
#include <iostream>

using namespace std;
using namespace cs225;

template class <class V=Vertex, class E=Edge>
class Graph {
    public:
        V & insertVertex(string key);
        E & insertEdge(const Vertex & v1, const Vertex & v2, string key);
        void removeVertex(const string & key);
        void removeEdge(const string & key);
        bool areAdjacent(const Vertex v1, const Vertex v2);
        E incidentEdges(const string key);
    private:
        list<E> edgeList;
        unordered_map<string, v> vMap;
        unordered_map<string, list<edgeListIter>> adjList:
};

#include "Graph.hpp"