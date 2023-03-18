#include <iostream>
#include <cstring>
#include <unistd.h>
#include "commandsender.h"

static std::string path = "/tmp/mpvsocket";

int MpvCommandClient::mpv_connect(){
    int rc;
    struct sockaddr_un sun;
    memset(&sun, 0, sizeof(sun));
    mpv_socket = socket(AF_LOCAL, SOCK_STREAM, 0);
    if (mpv_socket == -1) {
        return -1;
    }
    sun.sun_family = AF_LOCAL;
    strncpy(sun.sun_path, path.c_str(), path.size() + 1);
    rc = connect(mpv_socket, (const struct sockaddr*)&sun,
            sizeof(sun));
    if(rc < 0){
        std::cout << "connect error" << std::endl;
    }
    return rc;
}

void MpvCommandClient::mpv_recv(){
    int rc{0};
    std::string output;
    char buffer;
    do{
        buffer = 0;
        rc = recv(mpv_socket, &buffer, 1, 0);
        if(rc > 0){
            printf("%c", buffer);
        }
    }while(rc > 0);
    return;
}

int MpvCommandClient::mpv_send(const std::string &str){
    int rc{0};
    rc = send(mpv_socket, str.c_str(), str.size() + 1, 0);
    if(rc < 0){
        std::cout << "send error" << std::endl;
    }
    std::cout << str << std::endl;
    return rc;
}

int MpvCommandClient::mpv_send_safe(const std::string &str){
    int rc{0};
    rc = mpv_connect();
    if(rc < 0) return -1;
    rc = send(mpv_socket, str.c_str(), str.size() + 1, 0);
    if(rc < 0){
        std::cout << "send error" << std::endl;
    }
    std::cout << str << std::endl;
    sleep(1);
    rc = mpv_close();
    if(rc < 0) return -1;
    return rc;
}

int MpvCommandClient::mpv_close(){
    int rc{0};
    rc = close(mpv_socket);
    if(rc < 0){
        std::cout << "send error" << std::endl;
    }
    return rc;
}
