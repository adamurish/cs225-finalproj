// Include core graph class
#include "../graph/graph.h"

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
class AirGraph : private Graph {
    public:
        // Default air graph constructor
        AirGraph();

        // Airgraph destructor
        ~AirGraph();
        
        // Insert airports into graph from vector of vectors
        // @param vec Pointer to vector contiaing airport vector pointers
        void insertAirports(std::vector<std::vector<std::string>*>* vec);
        
        // Insert flights into graph from vector of vectors
        // @param vec Pointer to vector contiaing airport vector pointers
        void insertFLights(std::vector<std::vector<std::string>*>* vec);
        
        // Find shortest path between two airports
        // @param airport1 OpenFlights id of source airport
        // @param airport2 OpenFlights id of destination airport
        // @return Vector containing flights creating shortest path
        std::vector<flight> findShortestPath(Vertex airport1, Vertex airport2);
        
        // Find shortest landmark path
        // @param vec Vector of OpenFlight IDs of airports in order of visitation
        // @return Vector
        std::vector<flight> findLandmarkPath(std::vector<Vertex> vec);
    
    private:
        // Dictionary (Hash Map) to store airport details 
        std::unordered_map<Vertex, airport> airport_dict;

        // Dictionary (Hash Map) to store airline details
        std::unordered_map<Vertex, airline> airline_dict;

        // Vector of vector pointers to correlate flight data to graph
        std::vector<std::vector<flight>*> flight_board;

        // Helper function to parse user airport input
        // @param input User input string of IATA code or OpenFlights id
        // @return Vertex containing OpenFlights ID of requested airport
        Vertex airport_parser_ (string input);
};