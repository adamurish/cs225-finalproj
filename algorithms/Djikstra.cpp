#include <queue>

#include "../AirGraph/AirGraph.h"

std::unordered_map<Vertex, Vertex> AirGraph::Djikstra(const Vertex start) {    
    
    typedef std::pair<int, Vertex> vPair;
    
    // Unordered map that pairs vertex to it's distance from start vertex
    std::unordered_map<Vertex, int> dist;
    
    // Unordered map that pairs vertex label to a previous vertex label
    std::unordered_map<Vertex, Vertex> predecessor;

    // Unordered map that determines if vertex has been added to virtual "graph"
    std::unordered_map<Vertex, bool> virt_graph;
    
    //Goes through the vertices in the graph 
    //intializes the distances to INT_MAX and the predecessor to NULL sentinel
    for(Vertex v : getVertices()){
        dist[v] = INT_MAX;
        predecessor[v] = "";
    }

    // Set distance of source airport to zero
    dist[start] = 0;
    
    // Creates the priority queue to store vertices and distance pairs
    // This is a min heap as the lowest distance is first on queue
    std::priority_queue<vPair, std::vector<vPair>, std::greater<vPair>> pqueue;

    // Insert the source vertex into the priority queue
    pqueue.push(vPair(0, start));

    // Loop through every vertex in the graph
    while (!pqueue.empty()) {
        // Dequeue and store the vertex with the minimum distance from priority queue
        Vertex u = pqueue.top().second;
        pqueue.pop();
        // Add the vertex to the virtual graph as it is now visited
        virt_graph[u] = true;
        // Get all adjacent vertices of the vertex under examination
        for(Vertex v : getAdjacent(u)) {
            // Check if vertex v does not exists in virtual graph
            if (virt_graph.find(v) == virt_graph.end()) {
                // Get the weight of the current edge (u,v) u->v 
                int weight = getEdgeWeight(u, v);  
                // Instantiate current distance u
                int u_dist = dist[u];
                // Instantiate current distance v
                int v_dist = dist[v];
                // Checks to see if new distance is shorter than current distance
                if (u_dist + weight < v_dist){
                    //Update the distance of vertex v
                    int new_dist = u_dist + weight;
                    dist[v] = new_dist;
                    //Add the newly made vertex to the priority queue
                    pqueue.push(vPair(new_dist, v));
                    //Updates the predecessor map
                    predecessor[v] = u;
                }
            }
        }
    }
    // Return predecesor map
    return predecessor;
}
