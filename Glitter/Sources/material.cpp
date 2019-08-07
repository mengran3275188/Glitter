

#include "stb_image.h"

#include "material.hpp"

Material::Material(Dai::Shader *shader, std::map<std::string, std::string> const &textures) :mShader(shader)
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

		mTextures.insert(std::make_pair(texture, textureInfo.first));
	}
}

void Material::Activate(Camera &camera)
{
	mShader->activate();

	glm::mat4 view = camera.GetViewMatrix();
	glm::mat4 projection = camera.GetProjectionMatrix();
	glm::mat4 model = glm::mat4(1.0f);

	glUniformMatrix4fv(glGetUniformLocation(mShader->get(), "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(mShader->get(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(mShader->get(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

}

GLuint Material::GetShader() const
{
	return mShader->get();
}