#pragma once

#include <map>

#include "shader.hpp"
#include "camera.hpp"

class Material
{
public:
	Material(Dai::Shader *shader, std::map<std::string, std::string> const &textures);

	void Activate(Camera &camera);
	GLuint GetShader() const;

private:
	Dai::Shader* mShader;
	std::map<GLuint, std::string> mTextures;
};
