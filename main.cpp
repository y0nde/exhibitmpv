#include <mpv/client.h>
#include <iostream>
#include <string>
#include <sys/socket.h>

void check_error(int ec){
    std::cerr << mpv_error_string(static_cast<mpv_error>(ec)) << std::endl;
}

int main(int argc, const char** argv){
    if(argc < 2){
        std::cerr << "call with video file" << std::endl;
    }
    int ec;
    mpv_handle* handle = mpv_create();
    if(handle == NULL){
        std::cerr << "mpv_create fail" << std::endl; 
        exit(0);
    }

    mpv_set_option_string(handle, "input-default-bindings", "yes");
    mpv_set_option_string(handle, "input-vo-keyboard", "yes");
    int val = 1;
    mpv_set_option(handle, "osc", MPV_FORMAT_FLAG, &val);


    ec = mpv_initialize(handle);
    if(ec != MPV_ERROR_SUCCESS){
        check_error(ec);
        exit(0);
    }

    const char* command[] = {
        "loadfile",
        argv[1],
        NULL
    };

    ec = mpv_command(handle, command);
    if(ec != MPV_ERROR_SUCCESS){
        check_error(ec);
        exit(0);
    }

    while (1) {
        mpv_event *event = mpv_wait_event(handle, 10000);
        printf("event: %s\n", mpv_event_name(event->event_id));
        if (event->event_id == MPV_EVENT_SHUTDOWN)
            break;
    }

    mpv_terminate_destroy(handle);
    std::cout << "hh" << std::endl;
}
