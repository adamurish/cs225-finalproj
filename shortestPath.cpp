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

list<string> Graph::shortestPath(const Vertex start) {
    // Create a vector for distances and initialize all to infinity
    vector<int> dist(V, INF); 
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
    pqueue.buildHeap(g.getVertices())
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
        for(Vertex v : neighbors of u not in T){
            if(dist[u]+ cost(u,v)<dist[v]){
                dist[v] = dist[u] + cost(u,v);
                p[v] = u;
            }
        }
    }
    //**BFS code****
    // while(!queue.empty()){
    //     //store next vertex in queue to be examined
    //     v = queue.front();
    //     //print out bfs to terminal (Is this it?)
    //     cout << to_string(v) << " ";
    //     // Dequeue a vertex from queue
    //     queue.pop_front();
    //     // Get all adjacent vertices of the vertex under examination
    //     for (Vertex w: G.getAdjacent(v)){
    //         //Discovery Edge
    //         if (getVertexLabel(w) == "Unexplored"){
    //             //add a discovery edge labels
    //             setEdgeLabel(v, w, "Discovery");
    //             //update visited flag (TO VERTEX!)
    //             setEdgeLabel(w, "Visited");
    //             //update depth
    //             depth[w_next] = depth[w] + 1;
    //             //update predeccesor to vertex
    //             predecessor[w_next] = w;
    //             //Add the adjacent vertex to queue
    //             queue.push_back(*i);
    //         }
    //         //Cross Edge
    //         else if (getEdgeLabel(v, w) == "Unexplored"){
    //             //update edge with cross edge label 
    //             setEdgeLabel(v, w, "Cross")
    //         }
    //     }
    // }

}
