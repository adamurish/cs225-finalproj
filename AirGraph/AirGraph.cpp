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
            //each circle has raidus 2
            radii.push_back(2.0);
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
