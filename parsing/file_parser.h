#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::string;

class FileParser{
    private:
        std::vector<string>* csvline_to_vector(string line); //helper method
        std::vector<std::vector<string>*>* read_file(string file_name); //read file into vector of vectors of string
        std::vector<std::vector<string>*>* file;
    public:
        FileParser(string file_name); //constructor, mostly empty
        ~FileParser();
        std::vector<std::vector<string>*>* get_file();
};
