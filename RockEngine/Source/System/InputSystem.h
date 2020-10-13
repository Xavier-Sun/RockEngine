#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "System.h"
#include "Component\Input.h"

class InputSystem : public System
{
public:
	virtual void init() override;
	virtual void update() override;
};

#endif