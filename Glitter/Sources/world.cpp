#pragma once

#include <stb_image.h>
#include <iostream>

#include "world.hpp"

void World::Init()
{
	GLfloat skyboxVertices[] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	GLuint skyboxVBO;
	glGenVertexArrays(1, &mSkyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(mSkyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	/*
	mSkyboxTexture = LoadCubemap({ "/Resource/Textures/skybox/right.jpg", "/Resource/Textures/skybox/left.jpg",
				 "/Resource/Textures/skybox/top.jpg", "/Resource/Textures/skybox/bottom.jpg",
				 "/Resource/Textures/skybox/front.jpg", "/Resource/Textures/skybox/back.jpg",
		});


	mSkyboxShader = new Dai::Shader();
	mSkyboxShader->attach("skybox.vert");
	mSkyboxShader->attach("skybox.frag");
	mSkyboxShader->link();
	*/

	mPbrShader = new Dai::Shader();
	mPbrShader->attach("pbr.vert");
	mPbrShader->attach("pbr.frag");
	mPbrShader->link();

	Dai::Mesh *MyMesh = new Dai::Mesh("/Resource/Models/matBall.obj");
	Dai::Shader *MyShader = new Dai::Shader();
	MyShader->attach("test.vert");
	MyShader->attach("test.frag");
	MyShader->link();


	/*
	Material *MyMaterial = new Material(MyShader, { {"diffuse", "/Resource/Textures/metal_tiles_01/2K/Albedo.png"} });
	GameObject *MyGameobject = new GameObject(MyMesh, MyMaterial);
	mGameObjects.push_back(MyGameobject);
	*/

	Material *MyMaterial = new Material(mPbrShader, { 
		{"albedoMap", "/Resource/Textures/metal_tiles_01/2K/Albedo.png"},
		{"normalMap", "/Resource/Textures/metal_tiles_01/2K/TNormal.png"},
		{"metallicMap", "/Resource/Textures/metal_tiles_01/2K/Metallic.png"},
		{"roughnessMap", "/Resource/Textures/metal_tiles_01/2K/Roughness.png"},
		{"aoMap", "/Resource/Textures/metal_tiles_01/2K/AO.png"},
		});
	GameObject *MyGameobject = new GameObject(MyMesh, MyMaterial);
	mGameObjects.push_back(MyGameobject);
}

void World::Render(Camera camera)
{

	for each (GameObject* obj in mGameObjects)
	{
		obj->Render(camera);
	}

	glDepthFunc(GL_LEQUAL);
	//DrawSkybox(camera);
	glDepthFunc(GL_LESS);

}

GLuint World::LoadCubemap(std::vector<std::string> faces)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width, height, channels;
	for (unsigned int i = 0; i < faces.size(); ++i)
	{
		unsigned char *data = stbi_load((PROJECT_SOURCE_DIR + faces[i]).c_str(), &width, &height, &channels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else {
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return texture;
}

void World::DrawSkybox(Camera camera)
{
	mSkyboxShader->activate();

	glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
	glm::mat4 projection = camera.GetProjectionMatrix();

	glUniformMatrix4fv(glGetUniformLocation(mSkyboxShader->get(), "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(mSkyboxShader->get(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(mSkyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mSkyboxTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}


