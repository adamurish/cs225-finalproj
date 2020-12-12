// Define pi for spherical distance calculations
#define pi_over_180 0.017453292519943295769236907684886127134428718885417
// Store radius of earth for geospatial distance calculations
#define earth_R 6371E3

// Include AirGraph Header
#include "./AirGraph.h"
#include "../rendering/AirRenderer.h"
// Include cmath library for trig functions
#include <math.h>
#include <string>

AirGraph::AirGraph() : Graph(true, true), invalid(0) {
    // Do nothing
}

AirGraph::~AirGraph() {
    // Free memory from flights vector
    for (std::vector<flight>* route : routes) {
        // Delete current route
        delete route;
    }
}

void AirGraph::insertAirports(std::vector<std::vector<string>*>* vec) {
    // Loop through all airports in vector
    for (std::vector<string>* airportPtr : *vec) {
        // Store OpenFlights ID
        Vertex open_id = (*airportPtr)[0];
        
        // Insert new vertex into graph labeled with OpenFlights ID
        insertVertex(open_id);

        // Create a new airport to hold airport data
        airport currAirport;
        // Insert all values into airport struct
        currAirport.name = (*airportPtr)[1];
        currAirport.city = (*airportPtr)[2];
        currAirport.country = (*airportPtr)[3];
        currAirport.iata = (*airportPtr)[4];
        currAirport.icao = (*airportPtr)[5];
        currAirport.latitude = (*airportPtr)[6];
        currAirport.longitude = (*airportPtr)[7];
        currAirport.altitude = (*airportPtr)[8];
        currAirport.tz = (*airportPtr)[9];
        currAirport.dst = (*airportPtr)[10];
        currAirport.tz_olson = (*airportPtr)[11];
        currAirport.source = (*airportPtr)[13];

        // Insert airport into airports dictionary
        airports.insert(std::pair<Vertex, airport>(open_id, currAirport));

        // Check if IATA code exists
        if (currAirport.iata != "") {
            // Insert IATA -> OpenFlights_ID mapping into dictionary
            iata_to_id.insert(std::pair<string, Vertex>(currAirport.iata, open_id));
        }
    }
}

void AirGraph::insertFlights(std::vector<std::vector<string>*>* vec) {
    // Loop through all flights in vector
    for (std::vector<string>* flightPtr : *vec) {
        // Create a new flight to hold flight data
        flight currFlight;
        // Insert all values into flight struct
        currFlight.airline_open_ID = (*flightPtr)[1];
        currFlight.src_open_ID = (*flightPtr)[3];
        currFlight.dest_open_ID = (*flightPtr)[5];
        currFlight.codeshare = (*flightPtr)[6];
        currFlight.stops = (*flightPtr)[7];
        currFlight.equipment = (*flightPtr)[8];

        // Check if route exists between source and destination
        if (edgeExists(currFlight.src_open_ID, currFlight.dest_open_ID)) {
            // Get index of route in flight board
            int index = std::stoi(getEdgeLabel(currFlight.src_open_ID, currFlight.dest_open_ID));
            // Get pointer to route vector
            std::vector<flight>* route = routes[index];
            // Insert flight into route vector
            route->push_back(currFlight);
        }

        // Route doesn't exist yet between vertices
        else {
            // Get source airport iterator in map
            auto srcIt = airports.find(currFlight.src_open_ID);
            // Check if airport exists
            if (srcIt == airports.end()) { 
                // Increment number of invalid flights
                invalid ++;
                // Airport doesn't exist, continue to next route
                continue;
            }

            // Get destination iterator in map
            auto destIt = airports.find(currFlight.dest_open_ID);
            // Check if airport exists
            if (destIt == airports.end()) {
                // Increment number of invalid flights
                invalid ++;
                // Airport doesn't exist, continue to next route
                continue;
            }

            // Calculate index of next route vector
            int index = routes.size();

            // Insert edge between vertices
            insertEdge(srcIt->first, destIt->first);
            // Set edge weight to index of flights
            setEdgeLabel(srcIt->first, destIt->first, std::to_string(index));


            // Calculate distance of edge
            int weight = airport_dist_(srcIt->second, destIt->second);
            // Set weight of edge
            setEdgeWeight(srcIt->first, destIt->first, weight);
            
            // Create new vector for route
            std::vector<flight>* route = new std::vector<flight>();
            // Insert route vector into flight board at index
            routes.push_back(route);
            // Insert flight into route
            route->push_back(currFlight);
        }
    }
}

void AirGraph::storeAirlines(std::vector<std::vector<string>*>* vec) {
    // Loop through all airlines in vector
    for (std::vector<string>* airlinePtr : *vec) {
        // Store openID of current airline
        string open_id = (*airlinePtr)[0];

        // Create a new airline object
        airline currAirline;
        // Insert data in airline
        currAirline.name = (*airlinePtr)[1];
        currAirline.alias = (*airlinePtr)[2];
        currAirline.iata = (*airlinePtr)[3];
        currAirline.icao = (*airlinePtr)[4];
        currAirline.callsign = (*airlinePtr)[5];
        currAirline.country = (*airlinePtr)[6];
        currAirline.active = (*airlinePtr)[7];

        // Insert airline into airlines dictionary
        airlines.insert(std::pair<string, airline>(open_id, currAirline));
    }
}

int AirGraph::airport_dist_ (airport airport1, airport airport2) {
    // Calculate phi of airport 1
    double phi1 = std::stod(airport1.latitude) * pi_over_180;
    // Calculate phi of airport 2
    double phi2 = std::stod(airport2.latitude) * pi_over_180;
    // Calculate delta lambda
    double lambda = (std::stod(airport2.longitude) - std::stod(airport1.longitude)) * pi_over_180;
    // Calculate distance via Spherical Law of Cosines
    double d = acos((sin(phi1)*sin(phi2)) + (cos(phi1)*cos(phi2)*cos(lambda))) * earth_R;

    // Cast distance to int and return
    return (int) d;
}

int AirGraph::getNumFlights() {
    // The number of flights in the flight board
    int flights = 0;
    // Loop through all routes in the flight board
    for(std::vector<flight>* ptr : routes) {
        // Increment the number of flights
        flights += ptr->size();
    }
    // Return the number of flights
    return flights;
}

airport AirGraph::airportInfo(Vertex request) {
    // Check if airport does not exist
    if (airports.find(request) == airports.end()) {
        // Instantiate failed airport sentinel
        airport failed;
        failed.name = "Not found";
        failed.city = "Not found";
        failed.country = "Not found";
        failed.iata = "Not found";
        failed.icao = "Not found";
        failed.latitude = "Not found";
        failed.longitude = "Not found";
        failed.altitude = "Not found";
        failed.tz = "Not found";
        failed.dst = "Not found";
        failed.tz_olson = "Not found";
        failed.source = "Not found";

        // Return sentinel
        return failed;
    }
    // Get airport from map
    return airports[request];
}

cs225::PNG AirGraph::render(bool draw_airports, bool draw_flights) {
    //setup base map
    cs225::PNG base;
    base.readFromFile("mercator4.png");

    //initialize renderer with image and id -> airport map
    AirRenderer ar(base, airports);

    //setup vectors for render
    std::vector<double> radii;
    std::vector<airport> airport_vec;
    std::vector<flight> flight_vec;

    if(draw_airports) {
        for (const Vertex &v : getVertices()) {
            //each circle has raidus 5
            radii.push_back(5.0);
            //include every airport in the graph
            airport_vec.push_back(airports[v]);
        }
    }

    if(draw_flights) {
        for (auto route : routes) {
            //include the first flight of every route, since rest are duplicates
            flight_vec.push_back(route->at(0));
        }
    }
    //return the output of the render
    return ar.draw_airports_and_flights(airport_vec, radii, flight_vec);
}

cs225::PNG AirGraph::renderAirportRank(){
    //get weights from airport rank
    auto weights = airportRank(getVertices());
    //setup base map
    cs225::PNG base;
    base.readFromFile("mercator4.png");

    //initialize renderer with image and id -> airport map
    AirRenderer ar(base, airports);

    //setup radii from airport rank weights
    auto radii = std::vector<double>();
    //setup airports from corresponding vertices
    auto airport_vec = std::vector<airport>();
    for(const Vertex& v: getVertices()){
        radii.push_back(weights[v] * 5000.0);
        airport_vec.push_back(airports[v]);
    }

    return ar.draw_airports(airport_vec, radii);
}

cs225::PNG AirGraph::renderShortestPath(Vertex start, Vertex end, bool isBFS) {
    //setup base map
    cs225::PNG base;
    base.readFromFile("mercator4.png");

    //initialize renderer with image and id -> airport map
    AirRenderer ar(base, airports);

    // Store path from chosen algorithm
    std::unordered_map<Vertex, Vertex> travel = isBFS ? BFS(start) : Djikstra(start);

    // Get shortest path
    std::vector<Vertex> path = shortestPath(start, end, travel);
    
    // Create vector of flights
    std::vector<flight> flight_vec;
    // Create vector of airports
    std::vector<airport> airport_vec;
    std::vector<double> radii;
    Vertex last = start;
    //Loop through the shortest path
    for(const Vertex & v : path){
        // Retrace backwards through the vertex untill at start
        if(v != start) {
            // Add the current flight to the flight vectors
            flight_vec.push_back(routes[std::stoi(getEdge(last, v).getLabel())]->at(0));
            last = v;
        }
        // Add the current airport to the airport vectors
        airport_vec.push_back(airports[v]);
        radii.push_back(5.0);
    }
    // Return the rendered png of airports and flights
    return ar.draw_airports_and_flights(airport_vec, radii, flight_vec);
}

cs225::PNG AirGraph::renderBFS(Vertex start) {
    //setup base map
    cs225::PNG base;
    base.readFromFile("mercator4.png");

    //initialize renderer with image and id -> airport map
    AirRenderer ar(base, airports);

    //get BFS traversal
    auto path = BFS_Order(start);
    // Create vectors of airports and their radii
    std::vector<airport> airport_vec;
    std::vector<double> radii;
    // Insert start airport
    airport_vec.push_back(airports[start]);
    radii.push_back(5.0);
    // Insert all remaining airports
    for(const flight& f : path){
        airport_vec.push_back(airports[f.dest_open_ID]);
        radii.push_back(5.0);
    }

    return ar.draw_airports_and_flights(airport_vec, radii, path);
}

std::unordered_map<Vertex, double> AirGraph::airportRank(std::vector<Vertex> vertices) {
    //For more info see https://en.wikipedia.org/wiki/PageRank

    //This modified PageRank algorithm works by first constructing an adjacency matrix of the given vertices.
    //It then normalizes every column of the matrix to have a sum of 1, creating a markov matrix.
    //This markov matrix represents the probability of moving from one airport to another, assuming random choice.
    //The algorithm can then calculate the "steady-state" of the matrix by finding the eigenvector of the matrix
    //with eigenvalue 1, which is done by power iteration, multiplying the matrix by a random starting state
    //repeatedly, until it reaches the steady state. This steady state vector holds the probability of ending up at each
    //airport in the matrix after a long time, and thus can be used to determine their respective importances, the
    //airport with the highest probability is the most important, etc.

    //setup maps from Vertex to adj matrix index and vice versa
    //This is kind of messy, but allows for running airport rank on subgraphs
    std::unordered_map<Vertex, int> idx_map;
    std::unordered_map<int, Vertex> vertex_map;
    std::unordered_map<Vertex, double> ret;
    int current_idx = 0;
    for(const Vertex& v : vertices){
        idx_map[v] = current_idx;
        vertex_map[current_idx] = v;
        ret[v] = 0.0;
        current_idx++;
    }

    int num_airports = current_idx;

    auto adj_matrix = std::vector<std::vector<double>>(num_airports);
    for(auto &col : adj_matrix){
        col = std::vector<double>(num_airports, 0.0);
    }

    // populating adjacency matrix,
    // [i][j] is 1.0 if the vertices corresponding to index i and j are adjacent, if not it is 0.0
    for(const Vertex& v : vertices){
        for(const Vertex& adj : getAdjacent(v)){
            if(idx_map.count(adj) >= 1){
                adj_matrix[idx_map[v]][idx_map[adj]] = 1.0;
            }
        }
    }

    // normalizing adj_matrix
    for(auto &col : adj_matrix){
        double sum = 0.0;
        for(double val : col){
            sum += val;
        }
        for(double& val : col){
            //if sum is greater than 0, divide each value by sum to get norm
            if(sum > 0.0)
                val = val / sum;
            //if it is 0, the airport has no outgoing routes, so we assume that someone who is there will
            //randomly go to any other airport in the matrix (this is the assumption made in the original PageRank)
            else
                val = 1.0 / ((double) num_airports);
        }
    }
    //the adjacency matrix is now a markov matrix, as all of its columns add up to 1

    //perform power iteration on markov matrix
    //see https://en.wikipedia.org/wiki/Power_iteration for more info
    //Note that since we are performing it on a markov matrix, we are guaranteed that the largest eigenvalue will be 1

    //start vector is all 1/n
    auto b_k = std::vector<double>(num_airports, 1.0 / ((double) num_airports));
    //According to original paper, the algorithm generally converges good enough after 50 cycles
    //Could possibly lower this for efficiency
    int num_cycles = 50;
    for(int i = 0; i < num_cycles; ++i){
        b_k = multiply_matrix_(adj_matrix, b_k);
    }

    //insert weights into return map, which takes vertices to their probabilities
    for(int i = 0; i < num_airports; ++i){
        ret[vertex_map[i]] = b_k[i];
    }

    return ret;
}

std::vector<double> AirGraph::multiply_matrix_(std::vector<std::vector<double>> matrix, std::vector<double> vector) {
    //setup return vector
    auto ret = std::vector<double>(vector.size(), 0.0);

    //matrix must be square
    if(matrix.size() != matrix[0].size()) {
        std::cout << "Tried to call multiply matrix on non-square matrix" << std::endl;
        return ret;
    }

    //rows
    for(unsigned i = 0; i < matrix.size(); ++i){
        //columns
        for(unsigned j = 0; j < matrix.size(); ++j){
            // jth row of return vector is the linear combination of the jth row of matrix with vector as weights
            ret[j] += matrix[i][j] * vector[i];
        }
    }

    return ret;
}


std::string AirGraph::getAirportID(std::string airport) {
    // Get iterator to requested airport
    auto it = iata_to_id.find(airport);
    // Check if IATA exists
    if (it != iata_to_id.end()) {
        // Return the OpenFlights ID of the airport
        return it->second;
    }
    else {
        // OpenFlights ID not found, return "-1"
        return "-1";
    }
}