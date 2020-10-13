#ifndef EDITOR_UI_H
#define EDITOR_UI_H

#include <typeinfo>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Extern\ImGui\imgui.h"
#include "Extern\ImGui\imgui_impl_glfw.h"
#include "Extern\ImGui\imgui_impl_opengl3.h"
#include "Entity\Entity.h"
#include "Component\SceneBlock.h"
#include "Input.h"
#include "Graphics\Shader.h"
#include "Graphics\Model.h"
#include "Renderer.h"

class EditorUI
{
private:
	static Entity* selected_entity;
	static bool open_scene_block;
	static bool open_entities_block;
	static bool open_details_block;
	static bool open_resource_block;
	static bool open_settings_block;
	static bool open_demo;

	static void show_main_menu_bar();
	static void show_scene_block();
	static void show_entities_block();
	static void show_details_block();
	static void show_resource_block();
	static void show_settings_block();

	static void show_component_transform(Transform* p_transform);
	static void show_component_renderer(Renderer* p_renderer);

	static void show_children(Entity* p_entity);

	EditorUI() = delete;

public:
	static void init();
	static void update();
};

#endif