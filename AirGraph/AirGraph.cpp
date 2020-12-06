// Define pi for spherical distance calculations
#define pi_over_180 0.017453292519943295769236907684886127134428718885417
// Store radius of earth for geospatial distance calculations
#define earth_R 6371E3

// Include AirGraph Header
#include "./AirGraph.h"
// Include cmath library for trig functions
#include <math.h>
#include <string>

AirGraph::AirGraph() : Graph(true, true) {
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
        currAirport.source = (*airportPtr)[12];

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
            // Calculate index of next route vector
            int index = routes.size();

            // Insert edge between vertices
            insertEdge(currFlight.src_open_ID, currFlight.dest_open_ID);
            // Set edge weight to index of flights
            setEdgeLabel(currFlight.src_open_ID, currFlight.dest_open_ID, std::to_string(index));
            
            // Retrieve source airport
            airport src = airports[currFlight.src_open_ID];
            // Retreive destination airport
            airport dest = airports[currFlight.dest_open_ID];
            // Calculate distance of edge
            int weight = airport_dist_(src, dest);
            // Set weight of edge
            setEdgeWeight(currFlight.src_open_ID, currFlight.dest_open_ID, weight);
            
            // Create new vector for route
            std::vector<flight>* route = new std::vector<flight>();
            // Insert vector into flight board at index
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
