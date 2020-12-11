#include "./AirGraph/AirGraph.h"
#include "./parsing/file_parser.h"
#include "./cs225/PNG.h"
#include <iostream>

int print_help(){
    std::cout << "USAGE:" << std::endl;
    std::cout << "\t ./traffic /path/to/airports.dat /path/to/routes.dat [operation] [operation arguments]" << std::endl;
    std::cout << "OPERATIONS:" << std::endl;
    std::cout << "sssp : calculates single source shortest path using a specified traversal algorithm" << std::endl;
    std::cout << "\t-- Requires two additional arguments, the start and endpoint for the path, given as airport IATA codes" << std::endl;
    std::cout << "\t-- Requires a choice of traversal, either BFS or Djikstras" << std::endl;
    std::cout << "\t sssp [start_airport] [end_airport] [bfs, djikstra]" << std::endl;
    std::cout << "airportrank : Uses a modified version of Google's PageRank to calculate airport importance" << std::endl;
    std::cout << "bfs : Traverses the airport graph using breadth first search" << std::endl;
    std::cout << "\t-- Requires one additional argument, the starting point of traversal, given as airport IATA code" << std::endl;
    std::cout << "render : Renders all the airports in the dataset onto a world map" << std::endl;
    std::cout << "\t-- Requires one additional argument, [airports, routes, all], to set which objects to render" << std::endl;
    return 0;
}

int fail(string reason){
    std::cout << "Program has failed, reason: " << reason << std::endl;
    return 1;
}

int main(int argc, char* argv[]){
    AirGraph traffic;

    //input files (airports + routes)
    //algorithm to run

    if(argc == 2 && string(argv[1]) == "help")
        return print_help();

    if(argc < 4){  //Require 4 arguments
        std::cout<<"This program requires at least 3 command line arguments: A path to the airport dataset (airports.dat), a path to the route dataset (routes.dat), and an operation to run (one of [sssp, airportrank, bfs, render])"<<std::endl;
        std::cout << "Run './traffic help' for more information" << std::endl;
        return 1;
    }

    std::string airportsDataset = argv[1];
    std::string routesDataset = argv[2];
    std::string operation = argv[3];

    FileParser parseAirports(airportsDataset);
    std::vector<std::vector<string>*>* airports = parseAirports.get_file();
    traffic.insertAirports(airports);

    // FileParser parseAirlines("./datasets/airlines.dat");
    // std::vector<std::vector<string>*>* airlines = parseAirlines.get_file();
    // traffic.storeAirlines(airlines);

    FileParser parseRoutes(routesDataset);
    std::vector<std::vector<string>*>* routes = parseRoutes.get_file();
    traffic.insertFlights(routes);


    std::cout << "Airports Parsed: " << airports->size() << std::endl;
    std::cout << "Airports Stored: " << traffic.getVertices().size() << std::endl << std::endl;

    // std::cout << "Airlines Parsed: " << airlines->size() << std::endl;
    // std::cout << "Airlines Stored: " << traffic.getNumAirlines() << std::endl << std::endl;
    
    std::cout << "Flights Parsed: " << routes->size() << std::endl;
    std::cout << "Flights Stored: " << traffic.getNumFlights() << std::endl;
    std::cout << "Flights Invalid: " << traffic.getNumInvalidFlights() << std::endl;

    cs225::PNG image;

    if(operation == "sssp" && argc == 7){
        string id = traffic.getAirportID(argv[4]);
        string id2 = traffic.getAirportID(argv[5]);
        if(id == "-1" || id2 == "-1"){
            return fail("SSSP: Invalid airport IATA code");
        }
        string trav = argv[6];
        if(trav == "bfs") image = traffic.renderShortestPath(id, id2, true);
        else if(trav == "djikstra") image = traffic.renderShortestPath(id, id2, false);
        else return fail("SSSP: Invalid traversal");
    }
    else if (operation == "airportrank") {
        image = traffic.renderAirportRank();
    }
    else if (operation == "bfs" && argc == 5) {
        string id = traffic.getAirportID(argv[4]);
        if(id == "-1"){
            return fail("BFS: Invalid airport IATA code");
        }
        image = traffic.renderBFS(id);
    }
    else if (operation == "render" && argc == 5) {
        if(string(argv[4]) == "airports") image = traffic.render(true, false);
        else if(string(argv[4]) == "routes") image = traffic.render(false, true);
        else if(string(argv[4]) == "all") image = traffic.render(true, true);
        else return fail("RENDER: Invalid operation");
    }
    else {
        return fail("Invalid operation or missing arguments");
    }

    std::cout << "Saving result to output.png" << std::endl;

    image.writeToFile("./output.png");

    return 0;
}