#include <iostream>
#include <mutex>
#include <sys/socket.h>

std::string gen_load_command(std::string path){

}

std::string gen_property_command(std::string prop_name, std::string value){

}

class MpvCommandClient{
private:
    std::string mpv_socket_name;
    std::mutex mtx;
    int mpv_socket = 0;
public:
    ~MpvCommandClient();
    void set_mpv_socket_name(std::string path);
    int mpv_connect();
    int mpv_send(const std::string &str);
};

static MpvCommandClient mpv_command_client;
