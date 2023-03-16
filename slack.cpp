#include "slack.h"

#include <fstream>
#include <exception>

int SlackBot::run(){
    try{
        std::string mytoken;
        std::ifstream infile("token.txt");
        std::getline(infile, mytoken);
        {
            slack::create(mytoken);
        }
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
        return -1;
    }catch(...){
        std::cout << "some error happen." << std::endl;
        return -1;
    }
    return 0;
}

int SlackBot::send(const std::string &message){
    try{
        auto& slack = slack::instance();
        slack.chat.channel = "#mpvapp-log"; // required
        //slack.chat.username = "mpvappbot";   // optional check the doc
        slack.chat.postMessage(message);
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
        return -1;
    }catch(...){
        std::cout << "some error happen." << std::endl;
        return -1;
    }
    return 0;
}
