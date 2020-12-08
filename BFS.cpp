#include "graph.h"
#include <queue>
#include <string>
#include <list>
#include <unordered_map>
#include <iostream>
#include <algorithm>
//NEED TO INCLUDE!!!!!!!
//1.) set and get for Vertex Label
//2.) set and get for edge label 
//make sure it only takes either the vertex or edge as arguement but not both
//this implementation can't handle disjoint graphs
//fix predeccesor/depth calculations
using namespace std;
void Graph::BFS(const Graph G, const Vertex start)
{ 
    // (initialize) Mark all the vertices as not visited
    for(Vertex v: G.getVertices()){
        setVertexLabel(v, "Unexplored");
    }
    // (initialize) Mark all the edges as not visited
    for(Edge e: G.getVertices()){
        setEdgeLabel(e, "Unexplored");
    }

    // Create a queue for BFS
    list<string> queue;
    //label the current vertex
    Vertex curr = start;
    // Mark the current node as visited and enqueue it
    setEdgeLabel(v, "Visited");
    queue.push_back(curr);

    unordered_map<Vertex, Vertex> predecessor;
    unordered_map<Vertex, int> depth;

    while(!queue.empty()){
        //store next vertex in queue to be examined
        v = queue.front();
        //print out bfs to terminal (Is this it?)
        cout << to_string(v) << " ";
        // Dequeue a vertex from queue
        queue.pop_front();
        // Get all adjacent vertices of the vertex under examination
        for (Vertex w: G.getAdjacent(v)){
            //Discovery Edge
            if (getVertexLabel(w) == "Unexplored"){
                //add a discovery edge labels
                setEdgeLabel(v, w, "Discovery");
                //update visited flag (TO VERTEX!)
                setEdgeLabel(w, "Visited");
                //update depth
                depth[w_next] = depth[w] + 1;
                //update predeccesor to vertex
                predecessor[w_next] = w;
                //Add the adjacent vertex to queue
                queue.push_back(*i);
            }
            //Cross Edge
            else if (getEdgeLabel(v, w) == "Unexplored"){
                //update edge with cross edge label 
                setEdgeLabel(v, w, "Cross")
            }
        }
    }
} 

  