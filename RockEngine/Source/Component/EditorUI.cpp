#include "EditorUI.h"

Entity* EditorUI::selected_entity = nullptr;
bool EditorUI::open_scene_block = false;
bool EditorUI::open_entities_block = false;
bool EditorUI::open_details_block = false;
bool EditorUI::open_resource_block = false;
bool EditorUI::open_settings_block = false;
bool EditorUI::open_demo = false;

void EditorUI::show_main_menu_bar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Project"))
			{

			}
			if (ImGui::MenuItem("Open Project"))
			{

			}
			if (ImGui::MenuItem("Save"))
			{

			}
			if (ImGui::MenuItem("Save As..."))
			{

			}
			if (ImGui::MenuItem("Exit"))
			{
				Window::set_active(false);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Entity"))
		{
			if (ImGui::MenuItem("Create Empty Entity"))
			{

			}
			if (ImGui::MenuItem("Create Empty Child"))
			{

			}
			if (ImGui::BeginMenu("Simple Object"))
			{
				if (ImGui::MenuItem("Cube"))
				{

				}
				if (ImGui::MenuItem("Sphere"))
				{

				}
				if (ImGui::MenuItem("Capsule"))
				{

				}
				if (ImGui::MenuItem("Plane"))
				{

				}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Component"))
		{
			if (ImGui::MenuItem("Renderer", nullptr, false, selected_entity))
			{

			}
			if (ImGui::MenuItem("Custom Script", nullptr, false, selected_entity))
			{

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Block"))
		{
			ImGui::MenuItem("Scene", nullptr, &open_scene_block);
			ImGui::MenuItem("Entity", nullptr, &open_entities_block);
			ImGui::MenuItem("Details", nullptr, &open_details_block);
			ImGui::MenuItem("Resource", nullptr, &open_resource_block);
			ImGui::MenuItem("Settings", nullptr, &open_settings_block);
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void EditorUI::show_scene_block()
{
	ImGui::Begin("Scene", &open_scene_block);

	ImGui::GetWindowDrawList()->AddImage
	(
		(void*)SceneBlock::get_texture(),
		ImVec2(ImGui::GetCursorScreenPos()),
		ImVec2
		(
			ImGui::GetCursorScreenPos().x + ImGui::GetWindowContentRegionWidth(),
			ImGui::GetCursorScreenPos().y + ImGui::GetWindowContentRegionWidth() * SceneBlock::height / SceneBlock::width
		),
		ImVec2(0, 1),
		ImVec2(1, 0)
	);

	ImGui::End();
}

void EditorUI::show_entities_block()
{
	ImGui::Begin("Entity", &open_entities_block, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Create Entity"))
		{
			if (ImGui::MenuItem("Empty Entity"))
			{
				if (selected_entity == nullptr)
				{
					new Entity(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
				}
				else
				{
					new Entity(selected_entity, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
				}
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Cube"))
			{
				// TODO
			}
			if (ImGui::MenuItem("Sphere"))
			{
				// TODO
			}
			if (ImGui::MenuItem("Capsule"))
			{
				// TODO
			}
			if (ImGui::MenuItem("Plane"))
			{
				// TODO
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	show_children(Entity::root_entity);

	ImGui::End();
}

void EditorUI::show_details_block()
{
	ImGui::Begin("Details", &open_details_block);

	if (selected_entity)
	{
		ImGui::Checkbox(selected_entity->name.c_str(), &selected_entity->active);

		ImGui::Separator();

		for (auto component : selected_entity->components)
		{
			if (ImGui::CollapsingHeader(component->get_component_type_name().c_str()))
			{
				switch (component->get_component_type())
				{
				case ComponentType::TRANSFORM:
					show_component_transform((Transform*)component);
					break;
				case ComponentType::RENDERER:
					show_component_renderer((Renderer*)component);
					break;
				default:
					break;
				}
			}
		}

		if (ImGui::Button("Add Component"))
		{

		}

		if (ImGui::Button("Add Renderer Component"))
		{
			selected_entity->add_component<Renderer>();
		}
	}

	ImGui::End();
}

void EditorUI::show_resource_block()
{
	ImGui::Begin("Resource", &open_resource_block);

	if (ImGui::CollapsingHeader("Load Shader"))
	{
		static char shader_name[10];
		static char vs[50];
		static char fs[50];
		ImGui::InputText("Shader Name", shader_name, 10);
		ImGui::InputText("Vertex Shader Path", vs, 50);
		ImGui::InputText("Fragment Shader Path", fs, 50);

		if (ImGui::Button("OK"))
		{
			new Shader(shader_name, vs, fs);
		}
	}

	if (ImGui::CollapsingHeader("Load Model"))
	{
		static char model_name[10];
		static char path[50];
		ImGui::InputText("Model Name", model_name, 10);
		ImGui::InputText("Model Path", path, 50);

		if (ImGui::Button("OK"))
		{
			new Model(model_name, path);
		}
	}
	
	ImGui::End();
}

void EditorUI::show_settings_block()
{
	ImGui::Begin("Settings", &open_settings_block);

	ImGui::BulletText("Edit the background color of the scene block.");
	ImGui::ColorEdit4("Scene Background Color", glm::value_ptr(SceneBlock::background_color));

	ImGui::BulletText("Edit the style of the editor.");
	ImGui::ShowStyleEditor();

	ImGui::End();
}

void EditorUI::show_component_transform(Transform* p_transform)
{
	ImGui::InputFloat3("Position", glm::value_ptr(p_transform->position));
	ImGui::InputFloat3("Rotation", glm::value_ptr(p_transform->euler_angles));
	ImGui::InputFloat3("Scale", glm::value_ptr(p_transform->scale));
}

void EditorUI::show_component_renderer(Renderer* p_renderer)
{
	static char shader[10];
	static char model[10];

	ImGui::InputText("Shader", shader, 10);
	ImGui::InputText("Model", model, 10);

	if (ImGui::Button("Apply"))
	{
		p_renderer->shader = Shader::get_shader(shader);
		p_renderer->model = Model::get_model(model);
	}
}

void EditorUI::show_children(Entity* p_entity)
{
	if (p_entity != nullptr)
	{
		for (auto child : p_entity->children)
		{
			if (ImGui::TreeNode(child->name.c_str()))
			{
				selected_entity = child;

				show_children(child);

				ImGui::TreePop();
			}
		}
	}
}

void EditorUI::init()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(Window::get_window(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void EditorUI::update()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	show_main_menu_bar();
	if (open_scene_block)
	{
		show_scene_block();
	}
	if (open_entities_block)
	{
		show_entities_block();
	}
	if (open_details_block)
	{
		show_details_block();
	}
	if (open_resource_block)
	{
		show_resource_block();
	}
	if (open_settings_block)
	{
		show_settings_block();
	}
	if (open_demo)
	{
		ImGui::ShowDemoWindow();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
