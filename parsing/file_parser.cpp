#include "file_parser.h"


FileParser::FileParser(string file_name) : file_name(file_name){
    std::cout << "Parsing " << file_name << std::endl;
}

std::vector<std::vector<string>>* FileParser::read_file(){  //File parser to airport vector
    auto ret = new std::vector<std::vector<string>>(); //setup return vector
    std::ifstream airport_file; //create file object
    airport_file.open(file_name); //open file specified in constructor
    string f_line;
    if(airport_file.is_open()){ //if file opened successfully
        while(std::getline(airport_file, f_line)){ //while there's a line to read
            ret->push_back(csvline_to_vector(f_line)); //add processed line to return vector
        }
    }
    return ret; 
}
std::vector<string> FileParser::csvline_to_vector(string line){
    std::vector<string> ret;
    string tmp;
    for(char c : line){
        if(c == ','){
            ret.push_back(tmp);
            tmp = "";   //Reset tmp after every comma
        }else{
            tmp.push_back(c);   //Add every character of comma seperated entry to tmp string
        }
    }
    ret.push_back(tmp); //To catch last entry, which has no comma after it
    return ret;
}