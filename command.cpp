#include <iostream>

#include "command.h"

const std::string h_command = "\n{ \"command\": [\"";
const std::string t_command = "\"] }\n";
std::string CommandGenerator::loadfile(const std::string &path){
    const std::string s_loadfile = "loadfile\", \"";
    return h_command + s_loadfile + path + t_command;
}


std::string CommandGenerator::start(){
    const std::string s_start= 
        "set_property\", \"pause\", true";
    return h_command + s_start + t_command;
}

int command_test(int argc, char** argv){
    if(argc < 2){
        std::cout << "no args" << std::endl;
        exit(0);
    }
    std::string path = argv[1];
    CommandGenerator cg;
    std::cout << cg.loadfile(path) << std::endl;
    std::cout << cg.start() << std::endl;
    return 0;
}
