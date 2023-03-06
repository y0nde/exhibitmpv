#pragma once
#include <sys/socket.h>
#include <sys/un.h>

class MpvCommandClient{
private:
    int mpv_socket;
public:
    int mpv_connect(const std::string &socket_path);
    int mpv_send(const std::string &str);
    void mpv_recv();
    int mpv_close();
};
