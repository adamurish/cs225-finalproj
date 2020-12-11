#include "../cs225/catch/catch.hpp"
#include "../parsing/file_parser.h"
#include "../AirGraph/AirGraph.h"
#include "../graph/graph.h"
#include "../graph/edge.h"

//FILE PARSER TEST CASES

TEST_CASE("File parser reads correct number of lines", "[module=parsing]"){
    FileParser fp("tests/airport_csv_test.dat");

    //airport_csv_test.dat has 3 airports, so 3 lines
    REQUIRE(fp.get_file()->size() == 3);
}

TEST_CASE("File parser reads correct number of entries in each line", "[module=parsing]"){
    FileParser fp("tests/airport_csv_test.dat");

    for(auto line : *(fp.get_file())){
        //there are 14 entries per line in airport_csv_test.dat
        REQUIRE(line->size() == 14);
    }
}

TEST_CASE("File parser ignores commas in quotes", "[module=parsing]"){
    FileParser fp("tests/parser_test.dat");

    //parser_test.dat is one line with 3 entries
    //each entry has some extra commas inside the quotes
    //the parser should not use commas in quotes as separators, and should include them in the entry
    REQUIRE(fp.get_file()->size() == 1);
    REQUIRE(fp.get_file()->at(0)->size() == 3);
    REQUIRE(fp.get_file()->at(0)->at(0) == ",,,,,");
    REQUIRE(fp.get_file()->at(0)->at(1) == ", something something ,,, something else ,,,");
    REQUIRE(fp.get_file()->at(0)->at(2) == "normal entry");
}

// AirRenderer TEST CASES
TEST_CASE("AirRenderer renders Airports in correct location", "[module=AirRenderer]"){
    FileParser fp("tests/airport_csv_test.dat");
    AirGraph ag;
    ag.insertAirports(fp.get_file());
    auto render = ag.render(true, false);
    // map is 4800 x 4800, so manually doing the math the airports should be centered at
    // R = 763.944
    // London: x = 2393.84, y = 1596.91
    // Kugaaruk: x = 1202.559, y = 1129.463
    // Pokhara: x = 3519.761, y = 2007.816
    // AirRenderer should set these coordinates to have a hue of 0, so we will check that

    render.writeToFile("tests/render_output_1.png");
    REQUIRE(render.getPixel(2394, 1597).h == 0);
    REQUIRE(render.getPixel(1203, 1129).h == 0);
    REQUIRE(render.getPixel(3520, 2008).h == 0);
}

// AirGraph TEST CASES
TEST_CASE("AirGraph loads all airports", "[module=AirGraph]"){
    FileParser fp("tests/airport_csv_test.dat");
    AirGraph ag;
    ag.insertAirports(fp.get_file());
    REQUIRE(ag.getVertices().size() == 3);
}

TEST_CASE("AirGraph loads all routes", "[module=AirGraph]"){
    FileParser ap_fp("datasets/airports.dat");
    FileParser route_fp("tests/route_csv_test.dat");
    AirGraph ag;
    ag.insertAirports(ap_fp.get_file());
    ag.insertFlights(route_fp.get_file());
    REQUIRE(ag.getEdges().size() == 9);
}

// ALGORITHM TEST CASES
// THESE CASES REQUIRE THE FULL OPENFLIGHTS DATASETS

TEST_CASE("SSSP finds shortest path using BFS", "[module=algorithms]"){
    FileParser ap_fp("datasets/airports.dat");
    FileParser route_fp("datasets/routes.dat");
    AirGraph ag;
    ag.insertAirports(ap_fp.get_file());
    ag.insertFlights(route_fp.get_file());

    Vertex lax = ag.getAirportID("LAX");
    Vertex abt = ag.getAirportID("ABT");

    auto path = ag.shortestPath(lax, abt, ag.BFS(lax));
    REQUIRE(path.front() == lax);
    REQUIRE(path.back() == abt);
    //the shortest path from lax to abt uses only 1 stop in between
    REQUIRE(path.size() == 3);
}

TEST_CASE("SSSP finds shortest path using Djikstra", "[module=algorithms]"){
    FileParser ap_fp("datasets/airports.dat");
    FileParser route_fp("datasets/routes.dat");
    AirGraph ag;
    ag.insertAirports(ap_fp.get_file());
    ag.insertFlights(route_fp.get_file());

    Vertex lax = ag.getAirportID("LAX");
    Vertex abt = ag.getAirportID("ABT");

    auto path = ag.shortestPath(lax, abt, ag.Djikstra(lax));
    REQUIRE(path.front() == lax);
    REQUIRE(path.back() == abt);
    //the shortest path from lax to abt uses only 1 stop in between
    REQUIRE(path.size() == 3);
}

TEST_CASE("BFS properly traverses airports", "[module=algorithms]"){
    FileParser ap_fp("datasets/airports.dat");
    FileParser route_fp("datasets/routes.dat");
    AirGraph ag;
    ag.insertAirports(ap_fp.get_file());
    ag.insertFlights(route_fp.get_file());

    auto bfs = ag.BFS_Order(ag.getAirportID("LAX"));
    //check to make sure the BFS traversal goes to all airports around LAX before continuing deeper
    auto adj = ag.getAdjacent(ag.getAirportID("LAX"));
    for(unsigned i = 0; i < adj.size(); ++i) {
        Vertex vert = bfs[i].dest_open_ID;
        if (vert != "-1") {
            bool found = false;
            for (Vertex v : adj) {
                if (vert == v)
                    found = true;
            }
            if (!found) {
                std::cout << "Could not find " << ag.getAirportID(bfs[i].dest_open_ID) << std::endl;
            }
            REQUIRE(found == true);
        }
    }
}

TEST_CASE("AirportRank returns probabilities adding up to 1", "[module=algorithms]"){
    FileParser ap_fp("datasets/airports.dat");
    FileParser route_fp("datasets/routes.dat");
    AirGraph ag;
    ag.insertAirports(ap_fp.get_file());
    ag.insertFlights(route_fp.get_file());

    std::vector<Vertex> test_vertices = {ag.getAirportID("LAX"),ag.getAirportID("ORD"),ag.getAirportID("STL"),ag.getAirportID("ATL")};
    auto weights = ag.airportRank(test_vertices);
    double sum = 0.0;
    for(auto v : test_vertices){
        sum += weights[v];
    }
    REQUIRE(sum == 1.0);
}