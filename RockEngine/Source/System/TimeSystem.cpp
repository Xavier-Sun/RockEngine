#include "TimeSystem.h"

void TimeSystem::update()
{
    Time::current_time = glfwGetTime();
    Time::delta_time = Time::current_time - Time::last_frame_time;
    Time::last_frame_time = Time::current_time;
}
