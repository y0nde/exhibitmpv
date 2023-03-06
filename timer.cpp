#include <iostream>
#include <thread>
#include <chrono>

#include "timer.h"

using std::chrono::system_clock;

time_t now_epoch(){
    system_clock::time_point p = system_clock::now();
    std::chrono::seconds ps = 
        std::chrono::duration_cast<std::chrono::seconds>(
                p.time_since_epoch()
                );
    return ps.count();
}

void sleep_until_epoch_t(time_t t){
    std::cout << __FUNCTION__ << " waiting for " << t - now_epoch() << std::endl;
    system_clock::time_point p = system_clock::from_time_t(t);
    std::this_thread::sleep_until(p);
}

int timer_test(int argc, char** argv){
    if(argc < 2){
        std::cout << "no args" << std::endl;
        exit(0);
    }
    std::cout << "now " << now_epoch() << std::endl;
    std::cout << "waiting until " << argv[1] << std::endl;
    sleep_until_epoch_t(std::stoi(argv[1]));
    std::cout << "finish " << now_epoch() << std::endl;
    return 0;
}
