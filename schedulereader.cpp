#include <iostream>
#include <fstream>
#include <ctime>
#include <stdexcept>

#include "schedulereader.h"
#include "timer.h"

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

time_t today_start_epoch(){
    struct tm* time_point_ptr;
    time_t now = time(NULL); 
    time_point_ptr = localtime(&now);
    if(time_point_ptr == NULL){
        return -1;
    }
    time_point_ptr->tm_hour = 0;
    time_point_ptr->tm_min = 0;
    time_point_ptr->tm_sec = 0;
    time_t today_start_epoch = mktime(time_point_ptr);
    return today_start_epoch;
}

time_t conv_strt_time_t(const std::string& strt){
    struct tm parsed_time = {0};
    if(strptime(strt.c_str(), "%H:%M:%S", &parsed_time) == NULL){
        throw std::invalid_argument("format is %H:%M:%S");
    }else{
        long parsed_time_sec = parsed_time.tm_hour * 60 * 60 + parsed_time.tm_min * 60 + parsed_time.tm_sec;
        return parsed_time_sec;
    }
}

time_t conv_strt_today_time_t(const std::string& strt){
    time_t time_in_today = conv_strt_time_t(strt);
    return today_start_epoch() + time_in_today;
}

struct PlayEvent conv_strv_playevent(const std::vector<std::string> &strv){
    struct PlayEvent pe = {
        "", 0, 0
    };
    if(strv.size() >= 3){
        try {
            pe.path = strv[1];
            //pe.start_time = std::stol(strv[1]); 
            pe.start_time = conv_strt_today_time_t(strv[0]); 
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

