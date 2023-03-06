#include <thread>
#include <chrono>

using std::chrono::system_clock;

time_t now_epoch();

void sleep_until_epoch_t(time_t t);

