#include "System.h"

std::vector<System*> System::systems;

void System::init_all()
{
	for (auto i : systems)
	{
		i->init();
	}
}

void System::update_all()
{
	for (auto i : systems)
	{
		i->update();
	}
}

System::~System()
{
	for (auto i : systems)
	{
		delete i;
	}
}
