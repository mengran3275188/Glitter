

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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(image);

		mTextures.push_back(std::make_pair(texture, textureInfo.first));
	}
}

void Material::Activate(Camera &camera)
{
	mShader->activate();

	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = camera.GetProjectionMatrix();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, 0));

	glUniformMatrix4fv(glGetUniformLocation(mShader->get(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(mShader->get(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(mShader->get(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	/*
	glUniform3f(glGetUniformLocation(mShader->get(), "dirLight.direction"), -0.2f, -1.0f, -0.3f);
	glUniform3f(glGetUniformLocation(mShader->get(), "dirLight.ambient"), 0.55f, 0.55f, 0.55f);
	glUniform3f(glGetUniformLocation(mShader->get(), "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
	glUniform3f(glGetUniformLocation(mShader->get(), "dirLight.specular"), 0.5f, 0.5f, 0.5f);
	*/

	GLint viewPosLoc = glGetUniformLocation(mShader->get(), "viewPos");
	glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);
	GLint camPosLoc = glGetUniformLocation(mShader->get(), "camPos");
	glUniform3f(camPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

	glUniform1f(glGetUniformLocation(mShader->get(), "material.shininess"), 32);

	unsigned int unit = 0, diffuse = 0, specular = 0;
	for (auto &i : mTextures)
	{   // Set Correct Uniform Names Using Texture Type (Omit ID for 0th Texture)
		std::string uniform = i.second;

		// Bind Correct Textures and Vertex Array Before Drawing
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, i.first);

		GLint texLoc = glGetUniformLocation(mShader->get(), uniform.c_str());
		glUniform1f(texLoc, unit);
		unit++;

		//glUniform1f(glGetUniformLocation(mShader->get(), "material.diffuse"), 0);
	}
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
		GLint lightPositionLoc = glGetUniformLocation(mShader->get(), ("lightPositions[" + std::to_string(i) + "]").c_str());
		GLint lightColorLoc = glGetUniformLocation(mShader->get(), ("lightColors[" + std::to_string(i) + "]").c_str());
		glUniform3f(lightPositionLoc, lightPositions[i].x, lightPositions[i].y, lightPositions[i].z);
		glUniform3f(lightColorLoc, lightColors[i].x, lightColors[i].y, lightColors[i].z);
	}
}

GLuint Material::GetShader() const
{
	return mShader->get();
}