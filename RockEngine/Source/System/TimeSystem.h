#ifndef TIME_SYSTEM_H
#define TIME_SYSTEM_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "System.h"
#include "Component\Time.h"

class TimeSystem : public System
{
public:
	virtual void update() override;
};

#endif