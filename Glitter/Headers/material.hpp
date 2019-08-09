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

private:

	Dai::Shader* mShader;
	std::vector<std::pair<GLuint, std::string>> mTextures;
};
