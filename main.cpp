#include "./AirGraph/AirGraph.h"
#include "./parsing/file_parser.h"
#include "./cs225/PNG.h"
#include <iostream>

int main(int argc, char* argv[]){
    AirGraph traffic;

    //input files (airports + routes)
    //algorithm to run
    if(argc != 4){  //Require 4 arguments
        std::cout<<"This program requires 3 command line arguments: A path to the airport dataset (airport.dat), a path to the route dataset (routes.dat), and an operation to run (one of [sssp, landmark, airportrank, bfs])"<<std::endl;
        return 1;
    }

    std::string airportsDataset = argv[1];
    std::string routesDataset = argv[2];
    std::string operation = argv[3];

    std::cout << argc << std::endl;
    std::cout << argv[0] << std::endl;
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

    string id = traffic.getAirportID("ORD");
    string id2 = traffic.getAirportID("LAX");
    cs225::PNG image;

    if(operation == "sssp") image = traffic.renderShortestPath(id, id2);
    else if (operation == "landmark") image = traffic.renderLandmarkPath({id, id2});        
    else if(operation == "airportrank") image = traffic.renderAirportRank({id, id2});
    else if (operation == "bfs") image = traffic.renderBFS(id);
    else std::cout<<"Invalid operation 😂"<<std::endl;

    image.writeToFile("./testimage.png");

    // I don't know if you want to keep this
    //traffic.render().writeToFile("render.png");

    return 0;
}