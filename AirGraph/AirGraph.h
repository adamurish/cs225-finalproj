// Include core graph class
#pragma once

#include "../graph/graph.h"
#include "../cs225/PNG.h"

// Define airport structure
struct airport {
    // Airport full name
    string name;
    // City of airport
    string city;
    // ISO 3166-1 country code
    string country;
    // IATA airport identifier (Common 3 letter code)
    string iata;
    // ICAO code
    string icao;
    // Latitude (decimal degrees with up to 6 sig figs)
    string latitude;
    // Longitude (decimal degrees with up to 6 sig figs)
    string longitude;
    // Altitude (in feet)
    string altitude;
    // Hour offset from UTC (decimal)
    string tz;
    // Stores whether airport observes DST
    string dst;
    // Timezone in Olson format
    string tz_olson;
    // Airport data source
    string source;
};

// Define airline structure
struct airline {
    // Airline full name
    string name;
    // Airline friendly name
    string alias;
    // IATA code
    string iata;
    // ICAO code
    string icao;
    // Airline callsign
    string callsign;
    // ISO 3166-1 country code
    string country;
    // Whether airline is active or not
    //(**UNRELIABLE DATA SOURCE DO NOT USE**)
    string active;
};

// Define flight structure
struct flight {
    // Airline OpenFlights unique ID
    string airline_open_ID;
    // Source airport OpenFlights unique ID
    string src_open_ID;
    // Destination airport OpenFlights unique ID
    string dest_open_ID;
    // Codeshare (If yes Y, else empty)
    string codeshare;
    // Number of stops (0 for direct)
    string stops;
    // Types of planes flown (items separated by spaces)
    string equipment;
};


// Class to represent graph of air traffic
class AirGraph : public Graph {
    public:
        // Default AirGraph constructor
        AirGraph(); // Implemented

        // Airgraph destructor
        ~AirGraph(); // Implemented
        
        // Insert airports into graph from vector of vectors
        // @param vec Pointer to vector contiaing airport vector pointers
        void insertAirports(std::vector<std::vector<string>*>* vec); // Implemented
        
        // Insert flights into graph from vector of vectors after inserting airports
        // @param vec Pointer to vector contiaing airport vector pointers
        void insertFlights(std::vector<std::vector<string>*>* vec); // Implemented
        
        // Store airline data into airlines dictionary
        // @param vec Pointer to vector contiaing airlines vector pointers
        void storeAirlines(std::vector<std::vector<string>*>* vec); // Implemented

        // Helper function that gerenates a BFS traversal of the AirGraph from a given vertex.
        // Does not run against disconnected components not containing the starting airport
        // @param airport airport vertex from which to start BFS
        // @return Unoredered map of prdecessors
        std::unordered_map<Vertex,Vertex> BFS(const Vertex start);

        std::vector<flight> AirGraph::BFS_Order(const Vertex start);

        // ALL ALGOS WILL IMPLEMENT THIS INTERFACE
        // Djikstra's algorithm for Single Source Shortest Path
        // @param source Vertex key (OpenFlights ID) of requested source airport
        // @return Vector of airports Vertexes defining path
        std::unordered_map<Vertex, Vertex> Djikstra(const Vertex source);
        
        // function that returns the shortest path given a start and end vertex 
        // @param source Vertex key (OpenFlights ID) of requested source airport
        // @return Vector of airports Vertexes defining path
        std::vector<Vertex> shortestPath(const Vertex start, const Vertex end, std::unordered_map<Vertex, Vertex> predecessor);
        
        // Find shortest landmark path
        // @param vec Vector of OpenFlight IDs of airports in order of visitation
        // @return TBD
        std::vector<flight> findLandmarkPath(std::vector<Vertex> vec);

        // Modified PageRank to determine relative importance of Airports
        // @param vertices A vector of which vertices to rank
        // @return Unordered map connecting vertices to their relative importance
        std::unordered_map<Vertex, double> airportRank(std::vector<Vertex> vertices);

        // Return the number of airlines
        // @return Integer number of airlines
        int getNumAirlines() { return airlines.size(); };

        // Return the number of with invalid src/dest IDs
        // @return Integer number of invalid flights
        int getNumInvalidFlights() { return invalid; };

        // Return the number of flights
        // @return Integer number of flights
        int getNumFlights();

        // Return the OpenFlights ID of an airport given it's IATA
        // @param airport String containing the IATA of the target airport
        // @return String containing the OpenFlights ID of the requested airport ("-1" if not found)
        std::string getAirportID(std::string airport);

        // Return a render of the airports and flights on a world map
        // @param draw_airports Set if airports should be drawn
        // @param draw_flights Set if flights should be drawn
        cs225::PNG render(bool draw_airports, bool draw_flights);

        //Render airport rank of all airports in graph
        cs225::PNG renderAirportRank();

        //Render corresponding algorithms

        cs225::PNG renderShortestPath(Vertex start, Vertex end);

        cs225::PNG renderLandmarkPath(std::vector<Vertex> vec);

        cs225::PNG renderBFS(Vertex start);

    private:
        // Dictionary (Hash Map) to store OpenFlight_ID->airport mappings
        std::unordered_map<Vertex, airport> airports;

        // Dictionary (Hash Map) to store OpenFlight_ID->airline mappings
        std::unordered_map<Vertex, airline> airlines;

        // Dictionary (Hash Map) to store IATA->OpenFlight_ID mappings
        std::unordered_map<string, Vertex> iata_to_id;

        // Vector of vector pointers to correlate flight data to graph
        std::vector<std::vector<flight>*> routes;

        // Integer containing the number of invalid flights given
        int invalid;

        // Helper function to parse user airport input
        // @param input User input string of IATA code or OpenFlights id
        // @return Vertex containing OpenFlights ID of requested airport
        Vertex airport_parser_ (string input);

        // Helper function to calculate distance between two airports using the Spherical Law of Cosines
        // @param airport1 reference to first airport
        // @param airport2 refernece to second airport
        // @return Distance between airports as integer
        int airport_dist_ (airport airport1, airport airport2);

        // Internal helper to BFS iterations
        void AirGraph::BFS(std::unordered_map<Vertex, bool>& explored_verts, std::unordered_map<Vertex,Vertex>& traversal, std::vector<flight>& traversal_path, Vertex curr);

        // Helper function for AirportRank to multiply matrix by a vector
        std::vector<double> multiply_matrix_(std::vector<std::vector<double>> matrix, std::vector<double> vector);
};