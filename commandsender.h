#pragma once
#include <sys/socket.h>
#include <sys/un.h>

class MpvCommandClient{
private:
    int mpv_socket;
public:
    int mpv_connect();
    int mpv_send(const std::string &str);
    int mpv_send_safe(const std::string &str);
    void mpv_recv();
    int mpv_close();
};
