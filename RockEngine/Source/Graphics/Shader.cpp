#include "Shader.h"

std::vector<Shader*> Shader::collection;

Shader* Shader::get_shader(const std::string& p_name)
{
	for (auto shader : collection)
	{
		if (shader->name == p_name)
		{
			return shader;
		}
	}

	return nullptr;
}

void Shader::check_compile_error(unsigned int shader, ShaderType type)
{
	int success;
	char info_log[1024];
	switch (type)
	{
	case Shader::ShaderType::VERTEX_SHADER:
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, info_log);
			std::cout << "Failed to compile vertex shader, Error message:\n" << info_log << std::endl;
		}
		break;
	case Shader::ShaderType::FRAGMENT_SHADER:
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, nullptr, info_log);
			std::cout << "Failed to compile fragment shader, Error message:\n" << info_log << std::endl;
		}
		break;
	case Shader::ShaderType::PROGRAM:
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, nullptr, info_log);
			std::cout << "Failed to link program, Error message:\n" << info_log << std::endl;
		}
		break;
	default:
		break;
	}
}

void Shader::destroy(const std::string& p_name)
{
	auto shader = get_shader(p_name);
	if (shader != nullptr)
	{
		delete shader;
	}
}

Shader::Shader(const std::string& p_name, const char* vs_path, const char* fs_path)
{
	std::string vs_string = UtilityFunction::read_file(vs_path);
	std::string fs_string = UtilityFunction::read_file(fs_path);
	const char* vs_code = vs_string.c_str();
	const char* fs_code = fs_string.c_str();

	unsigned int vertex_shader;
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vs_code, nullptr);
	glCompileShader(vertex_shader);
	check_compile_error(vertex_shader, ShaderType::VERTEX_SHADER);

	unsigned int fragment_shader;
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fs_code, nullptr);
	glCompileShader(fragment_shader);
	check_compile_error(fragment_shader, ShaderType::FRAGMENT_SHADER);

	id = glCreateProgram();
	glAttachShader(id, vertex_shader);
	glAttachShader(id, fragment_shader);
	glLinkProgram(id);
	check_compile_error(id, ShaderType::PROGRAM);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	destroy(p_name);
	name = p_name;
	collection.push_back(this);
}

Shader::~Shader()
{
	glDeleteProgram(id);

	for (auto i = collection.begin(); i != collection.end(); i++)
	{
		if (*i == this)
		{
			collection.erase(i);
			break;
		}
	}
}

unsigned int Shader::get_id() const
{
	return id;
}

std::string Shader::get_name() const
{
	return name;
}

void Shader::set_name(const std::string& p_name)
{
	name = p_name;
}

void Shader::use()
{
	glUseProgram(id);
}

void Shader::set_int(const std::string& p_name, int value) const
{
	glUniform1i(glGetUniformLocation(id, p_name.c_str()), value);
}

void Shader::set_float(const std::string& p_name, float value) const
{
	glUniform1i(glGetUniformLocation(id, p_name.c_str()), value);
}

void Shader::set_vec2(const std::string& p_name, const glm::vec2& value) const
{
	glUniform2fv(glGetUniformLocation(id, p_name.c_str()), 1, glm::value_ptr(value));
}

void Shader::set_vec2(const std::string& p_name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(id, p_name.c_str()), x, y);
}

void Shader::set_vec3(const std::string& p_name, const glm::vec3& value) const
{
	glUniform3fv(glGetUniformLocation(id, p_name.c_str()), 1, glm::value_ptr(value));
}

void Shader::set_vec3(const std::string& p_name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(id, p_name.c_str()), x, y, z);
}

void Shader::set_vec4(const std::string& p_name, const glm::vec4& value) const
{
	glUniform4fv(glGetUniformLocation(id, p_name.c_str()), 1, glm::value_ptr(value));
}

void Shader::set_vec4(const std::string& p_name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(id, p_name.c_str()), x, y, z, w);
}

void Shader::set_mat2(const std::string& p_name, const glm::mat2& value) const
{
	glUniformMatrix2fv(glGetUniformLocation(id, p_name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_mat3(const std::string& p_name, const glm::mat3& value) const
{
	glUniformMatrix3fv(glGetUniformLocation(id, p_name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::set_mat4(const std::string& p_name, const glm::mat4& value) const
{
	glUniformMatrix4fv(glGetUniformLocation(id, p_name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
