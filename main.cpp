#include "./AirGraph/AirGraph.h"
#include "./parsing/file_parser.h"
#include <iostream>

int main(){

    AirGraph traffic;

    
    FileParser parseAirports("./datasets/airports.dat");
    std::vector<std::vector<string>*>* airports = parseAirports.get_file();
    traffic.insertAirports(airports);

    FileParser parseAirlines("./datasets/airlines.dat");
    std::vector<std::vector<string>*>* airlines = parseAirlines.get_file();
    traffic.storeAirlines(airlines);

    FileParser parseRoutes("./datasets/routes.dat");
    std::vector<std::vector<string>*>* routes = parseRoutes.get_file();
    traffic.insertFlights(routes);


    std::cout << "Airports Parsed: " << airports->size() << std::endl;
    std::cout << "Airports Stored: " << traffic.getVertices().size() << std::endl << std::endl;

    std::cout << "Airlines Parsed: " << airlines->size() << std::endl;
    std::cout << "Airlines Stored: " << traffic.getNumAirlines() << std::endl << std::endl;
    
    std::cout << "Flights Parsed: " << routes->size() << std::endl;
    std::cout << "Flights Stored: " << traffic.getNumFlights() << std::endl;
    std::cout << "Flights Invalid: " << traffic.getNumInvalidFlights() << std::endl;

    return 0;
}