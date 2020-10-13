#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>

#include "Utilities\UtilityFunction.h"

class Shader
{
private:
	enum class ShaderType
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		PROGRAM
	};

	unsigned int id;
	std::string name;

	void check_compile_error(unsigned int shader, ShaderType type);

public:
	static std::vector<Shader*> collection;
	static void destroy(const std::string& p_name);
	static Shader* get_shader(const std::string& p_name);

	Shader(const std::string& p_name, const char* vs_path, const char* fs_path);
	~Shader();
	unsigned int get_id() const;
	std::string get_name() const;
	void set_name(const std::string& p_name);
	void use();
	void set_int(const std::string& p_name, int value) const;
	void set_float(const std::string& p_name, float value) const;
	void set_vec2(const std::string& p_name, const glm::vec2& value) const;
	void set_vec2(const std::string& p_name, float x, float y) const;
	void set_vec3(const std::string& p_name, const glm::vec3& value) const;
	void set_vec3(const std::string& p_name, float x, float y, float z) const;
	void set_vec4(const std::string& p_name, const glm::vec4& value) const;
	void set_vec4(const std::string& p_name, float x, float y, float z, float w) const;
	void set_mat2(const std::string& p_name, const glm::mat2& value) const;
	void set_mat3(const std::string& p_name, const glm::mat3& value) const;
	void set_mat4(const std::string& p_name, const glm::mat4& value) const;
};

#endif