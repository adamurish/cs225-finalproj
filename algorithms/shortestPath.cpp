#include "./AirGraph/AirGraph.h"    
    
std::vector<Vertex> AirGraph::shortestPath(const Vertex start, const Vertex end) {
    // Vector that contains the shortest path from start to end vertices
    std::vector<string> path;
    
    // Query Djikstra's algorithm for shortest paths
    std::unordered_map<Vertex, Vertex> predecessor = Djikstra(start);

    // Create temp vertex to store end
    Vertex temp = end;
    // Add the end vertex to the start of path
    path.push_back(end);
    // Loops through the path from end to start
    while(temp != start){
        // Gets the previous vertex and stores it in the string vector
        path.push_back(predecessor[temp]);
        // Stores the previous vertex in temp vertex for later loops
        temp = predecessor[temp];
    }
    // Using STL reverse change the path so it goes from start to end vertex
    std::reverse(path.begin(), path.end());
    
    // Return vector of vertices that holds the shortest path from start vertex to end vertex
    return path;
}
