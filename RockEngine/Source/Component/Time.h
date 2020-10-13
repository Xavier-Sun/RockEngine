#ifndef TIME_H
#define TIME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Component.h"

class Time : public Component
{
private:
	static double delta_time;
	static double current_time;
	static double last_frame_time;

public:
	static double get_delta_time()
	{
		return delta_time;
	}

	static double get_current_time()
	{
		return current_time;
	}

private:
	Time() : Component(nullptr) {}

public:
	virtual ~Time() override {}

	Time(const Time&) = delete;

	Time& operator=(const Time&) = delete;

private:
	friend class TimeSystem;
};

#endif