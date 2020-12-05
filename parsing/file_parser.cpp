#include "file_parser.h"


FileParser::FileParser(string file_name) : file_name(file_name){
    file = read_file(file_name);
}

FileParser::~FileParser(){
    for(std::vector<string>* line : file){
        delete line;
    }
    delete file;
}

std::vector<std::vector<string>*>* FileParser::read_file(string file_name){  //File parser to airport vector
    auto ret = new std::vector<std::vector<string>*>(); //setup return vector
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

std::vector<string>* FileParser::csvline_to_vector(string line){
    auto ret = new std::vector<string>();
    string tmp;
    bool in_quotes = false;
    for(char c : line){
        if(c == ',' && !in_quotes){
            ret->push_back(tmp);
            tmp = "";   //Reset tmp after every comma
        }
        else if(c == '\"'){ //keep track of quoted text to ignore comments in names
            in_quotes = !in_quotes; //toggle quotes
        }
        else{
            tmp.push_back(c);   //Add every character of comma seperated entry to tmp string
        }
    }
    ret->push_back(tmp); //To catch last entry, which has no comma after it
    return ret;
}

std::vector<std::vector<string>*>* FileParser::get_file(){
    return file;
}
