#ifndef EDITOR_CAMERA_SYSTEM
#define EDITOR_CAMERA_SYSTEM

#include "System.h"
#include "Component\Input.h"
#include "Component\EditorCamera.h"
#include "Component\Time.h"

class EditorCameraSystem : public System
{
public:
	virtual void update() override;
};

#endif