#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::string;

// OLD STRUCT, REMOVED TO MAKE FILE PARSER MORE GENERALIZED

// struct airport
// {   
//     unsigned int airport_id; //unique airport id
//     string name; //name of aiport   
//     string city; //city airport is in
//     string country; //country airport is in
//     string IATA; //3 letter IATA code
//     string ICAO; //4 letter ICAO code
//     float latitude; //latitude in Decimal degrees, to 6 sig figs
//     float longitude; //longitude in Decimal degrees, to 6 sig figs
//     int altitude; //altitude in feet
//     double timezone; //hours offset from UTC, fractional hours possible
//     char dst;   //Daylight savings time
//     string tz;  //Time zone
//     string type;    //It's an airport
//     string source;  //Source of the datapoint for the airport
// };

class FileParser{
    private:
        string file_name;    //file to be parsed
        std::vector<string> csvline_to_vector(string line); //helper method
    public:
        FileParser(string file_name); //constructor, mostly empty
        std::vector<std::vector<string>>* read_file(); //read file into vector of vectors of strings
};
