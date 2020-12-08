#include "../cs225/catch/catch.hpp"
#include "../parsing/file_parser.h"
#include "../AirGraph/AirGraph.h"
#include "../graph/graph.h"
#include "../graph/edge.h"

TEST_CASE("Test Case Name")
{
	// Insert code to run here	
	//...
	//
	AirGraph traffic;

	// Require in order to pass case, aborts execution on failure
	REQUIRE(true);

	// Reuire in order to pass case, continues execution on failure
	CHECK(true);
};

//FILE PARSER TEST CASES

TEST_CASE("File parser reads correct number of lines", "[module=parsing]"){
    FileParser fp("tests/airline_csv_test.dat");

    //airline_csv_test.dat has 3 airports, so 3 lines
    REQUIRE(fp.get_file()->size() == 3);
}

TEST_CASE("File parser reads correct number of entries in each line", "[module=parsing]"){
    FileParser fp("tests/airline_csv_test.dat");

    for(auto line : *(fp.get_file())){
        //there are 14 entries per line in airline_csv_test.dat
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