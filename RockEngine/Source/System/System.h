#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>

class System
{
private:
	static std::vector<System*> systems;

public:
	static void init_all();
	static void update_all();
	template <typename T>
	static void add_system();

	virtual void init() {}
	virtual void update() {}

	~System();
};

template<typename T>
inline void System::add_system()
{
	systems.push_back(new T());
}

#endif