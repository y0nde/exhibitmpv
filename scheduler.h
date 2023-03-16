#pragma once

#include "commandsender.h"
#include "playevent.h"
#include "command.h"
#include "slack.h"

class Scheduler {
private:
    CommandGenerator cg;
    MpvCommandClient mcc;
    SlackBot sbot;
    std::string schedule_path;
public:
    Scheduler(const std::string &sp);
    struct PlayEvent next_playevent();
    int exec_event(const struct PlayEvent &event);
    int run();
};

