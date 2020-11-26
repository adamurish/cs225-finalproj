/* I know we need to include some things not sure what yet...

*/

/*insert vertex to graph and return the inserted vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(string key) {
}
/*insert edge to graph and return the inserted edge
using key as label
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const Vertex v1, const Vertex v2, string key) {
}



/*remove vertex
(possible to use vertex as well if keys not unique)
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const string & key) {
}
/*remove edge
(possible to use vertex as well if keys not unique)
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const string & key) {
}


/*
*/
template <class V, class E>
bool Graph<V,E>::areAdjacent(const Vertex v1, const Vertex v2) {
}
/*
*/
template <class V, class E>
E Graph<V,E>::incidentEdges(const Vertex v1) {
}




