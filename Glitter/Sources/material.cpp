

#include "stb_image.h"

#include "material.hpp"

Material::Material(Dai::Shader *shader, std::vector<std::pair<std::string, std::string>> const &textures) :mShader(shader)
{
	for each (auto textureInfo in textures)
	{
		std::string filepath = PROJECT_SOURCE_DIR + textureInfo.second;
		GLenum format;
		GLuint texture;
		int width, height, channels;
		unsigned char* image = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
		if (!image) fprintf(stderr, "%s %s\n", "Failed to Load Texture", filepath.c_str());

		switch (channels)
		{
		case 1:format = GL_ALPHA; break;
		case 2:format = GL_LUMINANCE; break;
		case 3:format = GL_RGB; break;
		case 4:format = GL_RGBA; break;
		default:
			format = GL_RGB;
			break;
		}
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(image);

		mTextures.push_back(std::make_pair(texture, textureInfo.first));
	}
}

void Material::Activate(Camera &camera, GLuint irradianceTexture)
{
	mShader->activate();

	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = camera.GetProjectionMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, 0));

	SetMat4("model", model);
	SetMat4("view", view);
	SetMat4("projection", projection);
	SetVec3("viewPos", camera.Position);
	SetVec3("camPos", camera.Position);

	unsigned int unit = 0, diffuse = 0, specular = 0;
	for (auto &i : mTextures)
	{   // Set Correct Uniform Names Using Texture Type (Omit ID for 0th Texture)
		std::string uniform = i.second;

		// Bind Correct Textures and Vertex Array Before Drawing
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, i.first);

		SetInt(uniform, unit);
		unit++;
	}
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, irradianceTexture);
	SetInt("irradianceMap", unit);
	SetInt("reflectionMap", unit);

	glm::vec3 lightPositions[] = {
	 glm::vec3(0.0f, 0.0f, 10.0f),
	};
	glm::vec3 lightColors[] = {
		glm::vec3(150.0f, 150.0f, 150.0f),
	};
	for (unsigned int i = 0; i < sizeof(lightPositions) / sizeof(lightPositions[0]); ++i)
	{
		//glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
		glm::vec3 newPos = lightPositions[i];
		SetVec3("lightPositions[" + std::to_string(i) + "]", lightPositions[i]);
		SetVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
	}
}

GLuint Material::GetShader() const
{
	return mShader->get();
}

void Material::SetBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(mShader->get(), name.c_str()), (int)value);
}
void Material::SetInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(mShader->get(), name.c_str()), value);
}
void Material::SetFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(mShader->get(), name.c_str()), value);
}
void Material::SetVec2(const std::string &name, const glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(mShader->get(), name.c_str()), 1, &value[0]);
}
void Material::SetVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(mShader->get(), name.c_str()), x, y);
}
void Material::SetVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(mShader->get(), name.c_str()), 1, &value[0]);
}
void Material::SetVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(mShader->get(), name.c_str()), x, y, z);
}
void Material::SetVec4(const std::string &name, const glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(mShader->get(), name.c_str()), 1, &value[0]);
}
void Material::SetVec4(const std::string &name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(mShader->get(), name.c_str()), x, y, z, w);
}
void Material::SetMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(mShader->get(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Material::SetMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(mShader->get(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Material::SetMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(mShader->get(), name.c_str()), 1, GL_FALSE, &mat[0][0]);
}