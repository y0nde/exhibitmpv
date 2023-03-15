#pragma once

#include <vector>

#include "playevent.h"

std::vector<struct PlayEvent> 
schedule_reader(const std::string &schedule_path);
int schedulereader_test();
