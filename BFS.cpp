#include "graph.h"
#include <queue>
#include <string>
#include <list>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;
void graph::BFS(const string start)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[numVertices];
    for(int i = 0; i < V; i++){
        visited[i] = false;
    }
    // Create a queue for BFS
    list<string> queue;
    //label the current vertex
    string curr = start;
    // Mark the current node as visited and enqueue it
    visited[start] = true;
    queue.push_back(s);
    //unordered_map<string, string> predecessor;
    //unordered_map<string, string> depth;

    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;
 
    while(!queue.empty())
    {
        //store next vertex in queue to be examined
        curr = queue.front();
        // Dequeue a vertex from queue
        queue.pop_front();
        // Get all adjacent vertices of the dequeued vertex dequeued
        for (i = adjacency_list[curr].begin(); i != adjacency_list[curr].end(); ++i){
            //adjcent vertex hasn't been visited
            if (!visited[*i]){
                //add a discoverg edge
                //discovery_edge = 
                //update visited flag
                visited[*i] = true;
                //update depth

                //update predeccesor to vertex

                //Add the adjacent vertex to queue
                queue.push_back(*i);
            }
            //else adjcent vertex has been visited
            else if (visited[*i] && ){ //cross label 
                queue.push_back(); 
            }
        }
    }
}