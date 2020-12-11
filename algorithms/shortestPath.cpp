#include "./AirGraph/AirGraph.h"    
    
std::vector<Vertex> AirGraph::shortestPath(const Vertex start, const Vertex end, std::unordered_map<Vertex, Vertex> predecessor) {
    // Vector that contains the shortest path from start to end vertices
    std::vector<string> path;
    
    // Create temp vertex to store end
    Vertex temp = end;
    
    // Add the end vertex to the start of path
    path.push_back(end);
    
    // Loops through the path from end to start
    while(temp != start && (predecessor.find(temp) != predecessor.end())) {
        // Gets the previous vertex and stores it in the string vector
        path.push_back(predecessor[temp]);
        // Stores the previous vertex in temp vertex for later loops
        temp = predecessor[temp];
    }

    // Check if path exists from start to requested end
    if (temp == start) {
        // Using STL reverse change the path so it goes from start to end vertex
        std::reverse(path.begin(), path.end());
    }

    else {
        // No path found, clear vector to print no flights
        predecessor.clear();
    }
    
    // Return vector of vertices that holds the shortest path from start vertex to end vertex
    return path;
}