#pragma once

#include "mesh.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "shader.hpp"

class GameObject
{
public:
	GameObject(Dai::Mesh* mesh, Material* material);
	void Render(Camera &camera, Material* overrideMat = nullptr);
	void SetIrradiance(GLuint texture);

	void SetPos(glm::vec3 inPos);
	void SetScale(glm::vec3 inScale);
private:

	GameObject(GameObject const &) = delete;
	GameObject& operator =(GameObject const &) = delete;
	Dai::Mesh* mMesh;
	Material* mMaterial;
	GLuint mIrradianceTexture;

	glm::vec3 mPos;
	glm::vec3 mScale;
};
