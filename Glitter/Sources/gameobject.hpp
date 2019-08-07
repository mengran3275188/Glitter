#pragma once

#include "mesh.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "shader.hpp"

class GameObject
{
public:
	GameObject(Dai::Mesh* mesh, Material* material);
	void Render(Camera &camera);
private:

	GameObject(GameObject const &) = delete;
	GameObject& operator =(GameObject const &) = delete;
	Dai::Mesh* mMesh;
	Material* mMaterial;
};
