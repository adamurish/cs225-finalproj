#include <queue>
#include <unordered_map>
#include <list>
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include<bits/stdc++.h> 
# define INF 0x3f3f3f3f 

using namespace std;

list<string> Graph::shortestPath(const Graph G, const Vertex start) {
    // Create a vector for distances and initialize all to infinity
    vector<int> dist(V, INF);
    vector<Vertex> p(V, NULL); 
    //set source distance to zero
    dist[start] = 0;
    //Goes through the vertices in the graph 
    //intializes the distances to infinity and the predecessor to NULL
    for(Vertex v : G){
        dist[V] = INF;
        p[v] = NULL;
    }   
    //creates the priority queue to store vertices and their weights
    priority_queue<weight, Vertex> pqueue;
    pqueue.buildHeap(G.getVertices())
    //*this varies depending on what you want to return*
    //Creates a graph to..
    Graph T;
    //loop that goes untill the priority queue is empty
    while(!pqueue.empty()){
    //gets the minumum distance from the priority queue
    //stores it in a vertex
    Vertex u = pqueue.top().second;
    T.add(u);
        //cost(u,v) is the weight from the current vertex to the next vertex
        bool isNeighbor = false;
        //for(Vertex v : neighbors of u not in T
        for(auto u : u.getAdjacent()){
            int weight = u.getEdgeWeight();
            if(dist[u]+ weight <dist[v]){
                dist[v] = dist[u] + weight;
                p[v] = u;
            }
        }
    }
 
}
