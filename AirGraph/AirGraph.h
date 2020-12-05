#include <unordered_map>

// Include core graph class
#include "../Graph/graph.h"

// Define airport structure
struct airport {
    // Airport full name
    string name;
    // City of airport
    string city;
    // ISO 3166-1 country code
    string country;
    // IATA airport identifier
    string iata;
    // ICAO code (Common 3 letter code)
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
    //(*** UNRELIABLE DATA SOURCE DO NOT USE ***)
    string active;
};

// Define flight structure
struct flight {
    // Airline ICAO code
    string icao;
    // Airline openFlights unique ID
    string open_ID;
    // Source airport ICAO code
    string src_icao;
    // Source airport openFlights unique ID
    string src_open_ID;
    // Destination airport ICAO code
    string dest_icao;
    // Destination airport openFlights unique ID
    string dest_open_ID;
    // Codeshare (If yes Y, else empty)
    string codeshare;
    // Number of stops (0 for direct)
    string stops;
    // Types of planes flown (items separated by spaces)
    string equipment;
};


// Class to represent graph of air traffic
// Wraps base graph class in order to tie multiple data structures
// together under one interface.
class AirGraph : private Graph {
    public:
        // Default air graph constructor
        AirGraph();
        // Insert airports into graph from vector of vectors
        void insertAirports(std::vector<std::vector<std::string>>
        );
        // Insert flights into graph from vector of vectors
        void insertFLights(std::vector<std::vector<std::string>>);
        // Find shortest path between two airports
        findShortestPath(std::string, std::string);
        // Find shortest landmark path
        findLandmarkPath(std::vector<std::vector<std::string>>);
    
    private:
        // Dictionary (Hash Map) to store airport details 
        std::unordered_map<Vertex, airport> airport_dict;
        // Dictionary (Hash Map) to store airline details
        std::unordered_map<Vertex, airline> airline_dict;
        // Vector of vectors to correlate flight data to graph
        std::vector<std::vector<flight>*> flight_board;

        // Helper function to parse user airport input
        // Accepts IATA or code openFlights id as input
        Vertex airport_parser_ (string input);
};