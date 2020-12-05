#include <iostream>
#include <fstream>
#include <vector>
#include <string>
// #include "../Graph/Graph.h"

using std::string;

// OLD STRUCT, REMOVED TO MAKE FILE PARSER MORE GENERALIZED


class FileParser{
    private:
        string file_name;    //file to be parsed
        std::vector<string> csvline_to_vector(string line); //helper method
   
    public:
        int iata_idx = 4;

        FileParser(string file_name); //constructor, mostly empty
        std::vector<std::vector<string>>* read_file(); //read file into vector of vectors of string
        /*Graph*/void airports_to_graph(std::vector<std::vector<string>>* airport_csv,
         std::vector<std::vector<string>>* routes_csv);
};
