#include <iostream>
#include <fstream>

#include "schedulereader.h"

std::vector<std::string> splitstr(std::string str, std::string delimeter = " "){
    std::vector<std::string> words;
    std::string::size_type pos;
    while((pos = str.find(delimeter))){
        words.push_back(str.substr(0, pos));
        str = str.substr(pos + 1);
        if(pos == str.npos){
            break;
        }
    }
    return words;
}

struct PlayEvent conv_strv_playevent(const std::vector<std::string> &strv){
    struct PlayEvent pe = {
        "", 0, 0
    };
    if(strv.size() >= 3){
        try {
            pe.path = strv[0];
            pe.start_time = std::stol(strv[1]); 
            pe.playlength = std::stol(strv[2]); 
        }
        catch(...) { return pe; }
    }
    return pe;
}

struct PlayEvent conv_str_playevent(const std::string &str){
    return conv_strv_playevent(splitstr(str));
}

std::vector<struct PlayEvent> schedule_reader(const std::string &schedule_path){
    std::vector<struct PlayEvent> pes;
    std::fstream fs(schedule_path);
    if(!fs){
        std::cerr << "fstream error" << std::endl;
        return pes;
    }
    while(!fs.eof()){
        std::string event_str;
        std::getline(fs, event_str);
        struct PlayEvent pe = conv_str_playevent(event_str);
        if(!pe.path.empty()){
            pes.push_back(pe);
        }
    }
    return pes;
}

int schedulereader_test(){
    std::vector<struct PlayEvent> pes = 
        schedule_reader("file.txt");
    for(const struct PlayEvent &pe : pes){
        std::cout << pe.path << std::endl;
        std::cout << pe.start_time << std::endl;
        std::cout << pe.playlength << std::endl;
    }
    return 0;
}

