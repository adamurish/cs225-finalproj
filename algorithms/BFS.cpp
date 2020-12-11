#include <queue>

#include "../AirGraph/AirGraph.h"

std::unordered_map<Vertex,Vertex> AirGraph::BFS(const Vertex start) {
    // Unordered map correlating vertex labels to exploration state
    // false: Unexplored, true: Explored
    std::unordered_map<Vertex, bool> explored_v;

    // Vector containing order of traversal
    std::unordered_map<Vertex,Vertex> traversal;

    // Vector containing order of traversal
    std::vector<flight> traversal_path;

    // (initialize) Mark all the vertices as unexplored
    for(Vertex v: getVertices()) {
        // Insert vertex pair into exploration map
        explored_v[v] = false;
    }

    // Run BFS initially on start vertex
    BFS(explored_v, traversal, traversal_path, start);

    // Loop through all vertices in order to traverse disconnected components
    for (Vertex curr : getVertices()) {
        // Only rerun BFS on vertex if not already discovered
        if (!explored_v[curr]) {
            // Run BFS on current vertex
            BFS(explored_v, traversal, traversal_path, curr);
        }
    }
    // Return vector containing routes traverses via exemplar first flight in route
    return traversal;
}

std::vector<flight> AirGraph::BFS_Order(const Vertex start) {
    // Unordered map correlating vertex labels to exploration state
    // false: Unexplored, true: Explored
    std::unordered_map<Vertex, bool> explored_v;

    // Vector containing order of traversal
    std::unordered_map<Vertex,Vertex> traversal;

    // Vector containing order of traversal
    std::vector<flight> traversal_path;

    // (initialize) Mark all the vertices as unexplored
    for(Vertex v: getVertices()) {
        // Insert vertex pair into exploration map
        explored_v[v] = false;
    }

    // Run BFS initially on start vertex
    BFS(explored_v, traversal, traversal_path, start);

    // Loop through all vertices in order to traverse disconnected components
    for (Vertex curr : getVertices()) {
        // Only rerun BFS on vertex if not already discovered
        if (!explored_v[curr]) {
            // Run BFS on current vertex
            BFS(explored_v, traversal, traversal_path, curr);
        }
    }
    // Return vector containing routes traverses via exemplar first flight in route
    return traversal_path;
}
    
void AirGraph::BFS(std::unordered_map<Vertex, bool>& explored_verts, std::unordered_map<Vertex,Vertex>& traversal, std::vector<flight>& traversal_path, Vertex curr) {
    // Create a queue for BFS
    std::queue<string> q;
    
    // Mark the current vertex as explored
    explored_verts[curr] = true;
    
    // Push the starting vertex into the queue
    q.push(curr);

    // Repeat until all vertices have been visited
    while(!q.empty()){
        // Dequeue and store next vertex
        Vertex v = q.front();
        q.pop();
        // Get all adjacent vertices of the vertex under examination
        for (Vertex w: getAdjacent(v)) {
            // Check if new vertex discovered
            if (!explored_verts[w]) {
                // Label vertex as explored
                explored_verts[w] = true;
                // Add the adjacent vertex to queue
                q.push(w);
                // Add current node to predecesor list of neighbor
                traversal[w] = v;
                // Add the first flight in route to the traversal vector
                traversal_path.push_back(routes[std::stoi(getEdgeLabel(v,w))]->at(0));
            }
        }
    }
} 
