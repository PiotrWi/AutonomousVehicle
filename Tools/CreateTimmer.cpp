#include "CreateTimmer.hpp"

#include <signal.h>
#include <cassert>
#include <iostream>

std::function<void()> UserHandler;

void timerHandler2(union sigval)
{
    if (UserHandler)
    {
        UserHandler();
    }
}

namespace tools
{

int createRepeatingTimer(int microseconds, std::function<void()> callback)
{
    UserHandler = callback;

    sigevent sig = {};
    timer_t timerId;
    sig.sigev_notify = SIGEV_THREAD;
    sig.sigev_notify_function = &timerHandler2;

    if (timer_create(CLOCK_REALTIME, &sig, &timerId))
    {
        std::cerr << "Timer crete failed" << std::endl;
        perror("errno");
        assert(0);
    }

    itimerspec input = {};
    input.it_interval.tv_sec = microseconds / 1000000;
    input.it_interval.tv_nsec = (microseconds % 1000000) * 1000;
    input.it_value.tv_sec = microseconds / 1000000;
    input.it_value.tv_nsec = (microseconds % 1000000) * 1000;
    if (timer_settime(timerId, 0, &input, NULL))
    {
        std::cerr << "Timer start failed" << std::endl;
        perror("errno");
        assert(0);
    }

    return 0;
}

}  // namespace tools