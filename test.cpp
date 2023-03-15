#include <iostream>
#include <vector>
#include <thread>

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "scheduler.h"
#include "schedulereader.h"

int main(int argc, const char** argv){
    if(argc < 2){
        std::cerr << "no args" << std::endl;
    }

    //schedulereader_test();
    Scheduler scheduler(argv[1]);
    scheduler.run();
}
