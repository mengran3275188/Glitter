#pragma once

#include <unordered_map>
#include <vector>

#include "shader.hpp"
#include "camera.hpp"

class Material
{
public:
	Material(Dai::Shader *shader, std::vector<std::pair<std::string, std::string>> const &textures);

	void Activate(Camera &camera);
	GLuint GetShader() const;

	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string & name, float value) const;
	void SetVec2(const std::string &name, const glm::vec2 &value) const;
	void SetVec2(const std::string &name, float x, float y) const;
	void SetVec3(const std::string &name, const glm::vec3 &value) const;
	void SetVec3(const std::string &name, float x, float y, float z) const;
	void SetVec4(const std::string &name, const glm::vec4 &value) const;
	void SetVec4(const std::string &name, float x, float y, float z, float w) const;
	void SetMat2(const std::string &name, const glm::mat2 &mat) const;
	void SetMat3(const std::string &name, const glm::mat3 &mat) const;
	void SetMat4(const std::string &name, const glm::mat4 &mat) const;

private:

	Dai::Shader* mShader;
	std::vector<std::pair<GLuint, std::string>> mTextures;
};
