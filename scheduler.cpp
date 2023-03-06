#include <iostream>
#include <vector>

#include <stdlib.h>
#include <unistd.h>

#include "scheduler.h"
#include "command.h"
#include "commandsender.h"
#include "schedulereader.h"
#include "playevent.h"
#include "timer.h"

Scheduler::Scheduler(const std::string &sp){
    schedule_path = sp;
}

struct PlayEvent Scheduler::next_playevent(){
    std::vector<struct PlayEvent> events =
        schedule_reader(schedule_path);
    struct PlayEvent npe = {"", 0, 0};
    time_t now = now_epoch();
    for(auto& pe : events){
        if(pe.start_time > now){
            if(npe.start_time == 0){
                npe = pe;
            }else{
                if( (npe.start_time - now) 
                        > (pe.start_time - now) ){
                    npe = pe;
                }
            }
        }
    }
    return npe;
}

int Scheduler::exec_event(const struct PlayEvent &event){
    std::string command = cg.loadfile(event.path);
    std::string start = cg.start();
    sleep_until_epoch_t(event.start_time);
    if(mcc.mpv_send(command) < 0){
        std::cerr << __FUNCTION__ << " fail" << std::endl;
        return -1;
    }
    //if(mcc.mpv_send(start) < 0){
        //std::cerr << __FUNCTION__ << " fail" << std::endl;
        //return -1;
    //}
    //mcc.mpv_recv();
    return 0;
}

int Scheduler::run(){
    if(mcc.mpv_connect("/tmp/mpvsocket") < 0){
        return 0;
    }
    while(1){
        //if(mcc.mpv_connect("/tmp/mpvsocket") < 0){
            //return 0;
        //}
        struct PlayEvent event = {"", 0, 0};
        event = next_playevent();
        if(event.start_time == 0){
            std::cerr << "can't find event" << std::endl;
            return 0;
        }
        exec_event(event);
        //mcc.mpv_close();
    }
}
