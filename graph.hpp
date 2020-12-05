/* I know we need to include some things not sure what else
*/
#include "graph.h"
#include <unordered_map>
#include <iostream>
#include <string>

using namespace std;
using namespace cs225;

/*insert vertex to graph and return the inserted vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(string key) {
    V & vertex = *(new v(key));     //creates new vertex given the key (assume that all keys are unique?)
    vMap.insert({key,vertex}); //add the newly created vertex to map
    adjList.insert({key, list<edgeListIter>()}) //add the vertex to adjlist
    //if we use areadjacent alot might use adj matrix instead... so add col and row
    return vertex;
}

/*insert edge to graph and return the inserted edge
using key as label
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const Vertex & v1, const Vertex & v2, string key) {
    E & edge = *(new E(v1, v2));    //creates a new edge with given vertices
    edgeList.push_front(edge);      //insert the edge to front of the edgelist
    adjList.at(v1.key()).push_front(edgeList.begin())); //add the new edge to the front of the adjlist
    //adjList.at(v2.key()).push_front(edgeList.begin())); //undirected graph?
    //if we use areAdjacent alot then might use adj matrix... so at ptr in matrix
    return edge;
}


/*remove vertex
garbo ;(
(possible to use vertex as well if keys not unique)
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const string & key) {
}
/*remove edge
garbo ;(
(possible to use vertex as well if keys not unique)
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const string & key) {
}


/*
*/
template <class V, class E>
bool Graph<V,E>::areAdjacent(const string key1, const string key2) const {
    for(auto it : adjlist(key1)){   //go through the adjacency list 
        E compareEdge = *it.get();  //store the current edge
        if(compareEdge.source().key() == key2 || compareEdge.dest().key() == key2){ //checks to see if the keys of the edges match meaning they are adjacent
            return true;    //if they match then they are adjacent
        }
    }
    return false;  
}
/*use refernce wrapper 
*/
template <class V, class E>
E list<reference_wrapper<E>> Graph<V,E>::incidentEdges(const string key) const{
    list<reference_wrapper<E>> edges;
    for(auto it : adjList.at(key)){  //goes through adjList
        edges.push_back(*it);       //adds to list if outbound edge
    }
    return edges;   //returns the set of edges that were incident to vertex
}




