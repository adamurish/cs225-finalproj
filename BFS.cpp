#include <queue>

#include "./AirGraph/AirGraph.h"

//NEED TO INCLUDE!!!!!!!
//this implementation can't handle disjoint graphs
//fix predeccesor/depth calculations

std::vector<string> AirGraph::BFS(const Vertex airport) {
    // Unordered map correlating vertex labels to exploration state
    // false: Unexplored, true: Explored
    std::unordered_map<Vertex, bool> explored_v;

    // Unordered map correlating edges labels to exploration state
    // false: cross, true: discovery
    std::unordered_map<string, bool> discovery_e;

    // Vector containing order of traversal
    std::vector<string> traversal;

    // (initialize) Mark all the vertices as unexplored
    for(Vertex v: getVertices()) {
        // Insert vertex pair into exploration map
        explored_v[v] = false;
    }
    // (initialize) Mark all the edges as unexplored
    for(Edge e: getEdges()) {
        // Insert edge pair into exploration map
        discovery_e[e.getLabel()] = false;
    }

    // Create a queue for BFS
    std::queue<string> q;
    
    // Mark the starting vertex as explored
    explored_v[airport] = true;
    
    // Push the starting vertex into the queue
    q.push(airport);

    // Repeat until all vertices have been visited (within connected component)
    while(!q.empty()){
        // Dequeue and store next vertex
        Vertex v = q.front();
        q.pop();
        // Get all adjacent vertices of the vertex under examination
        for (Vertex w: getAdjacent(v)) {
            // Check if new vertex discovered
            if (!explored_v[w]) {
                // Label edge as explored edge (dicovery is unneeded)
                discovery_e[getEdgeLabel(v, w)] = true;
                // Label vertex as explored
                explored_v[w] = true;
                // Add the adjacent vertex to queue
                q.push(w);
            }
            //Cross Edge
            //else if (!discovery_e[getEdgeLabel(v, w)]){ //getEdgeLabel(v, w) == "Unexplored"
            //    //update edge with cross edge label
            //    discovery_e[getEdgeLabel(v, w)] = true; //setEdgeLabel(v, w, "Cross")
            }
        }
    }
    //returns a vector of edges 
    return traversal;
} 

  