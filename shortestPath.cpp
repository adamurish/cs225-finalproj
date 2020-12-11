#include <utility>
#include<bits/stdc++.h> 
# define INF 0x3f3f3f3f 


#include "./AirGraph/AirGraph.h"

std::vector<string> AirGraph::shortestPath(const Vertex airport, const Vertex end) {    
    // Unordered map that pairs vertex to it's distance from start vertex
    std::unordered_map<Vertex, int> dist;
    
    // Creates a vector of vertex string that returns the shortest path from source to destination
    std::vector<string> path;
    
    // Creates the priority queue to store vertices and distance pairs
    // this is a min heap as the lowest distance in first on queue
    std::priority_queue<int, Vertex, greater<int> > pqueue;
    
    // Unordered map that pairs vertex label to a previos vertex label (NOT NEEDED?)
    std::unordered_map<Vertex, Vertex> predecessor;
    
    //Goes through the vertices in the graph 
    //intializes the distances to infinity and the predecessor to NULL
    for(Vertex v : getVertices()){
        dist[V] = INF;
        predecessor[v] = NULL;
    }   
    
    //insert the source vertex into the priority queue
    pqueue.push(make_pair(0, airport));
    
    //set distance of source airport to zero
    dist[airport] = 0;
    
    //set predeccesor of source to start
    predecessor[airport] = "start"; //vertex and string interchangable?

    //loop that goes untill the priority queue is empty
    while(!pqueue.empty()){
        //Dequeue and store the vertex with the minimum distance from priority queue
        Vertex u =  pqueue.top().second();
        pqueue.pop();
        // Get all adjacent vertices of the vertex under examination
        for(Vertex v : getAdjacent(u)){ 
            //Get the weight of the current edge (u,v) u->v 
            int weight = getEdgeWeight(u);  //this might need to be v instead of u...
            //checks to see if the edge adjacent to u is the shortest path
            if(dist[u]+ weight < dist[v]){
                //update the distance of vertex v
                dist[v] = dist[u] + weight;
                //add the newly made vertex to the priority queue
                pqueue.push(make_pair(dist[v], v));
                //updates the predecessor map
                predecessor[v] = u;
            }
        }
    }

    //Now that we have a list of predecessors we can retrace the steps 
    //for the shortest path from start to end

    //create temp vertex to store end
    Vertex temp = end;
    //add the end vertex to the start of path
    path.push_back(end);
    //loops through the path from end to start
    while(temp != start){
        //gets the previous vertex and stores it in the string vector
        path.push_back(predecessor[temp]);
        //stores the previous vertex in temp vertex for later loops
        temp = predecessor[temp];
    }

    //using STL reverse change the path so it goes from start to end vertex
    std::reverse(path.begin(), path.end());

    //return vector of vertices that holds the shortest path 
    //from start vertex ot end vertex
    return path;
}

