#pragma once
#include "world.hpp"

void World::Init()
{
	Dai::Mesh *MyMesh = new Dai::Mesh("/Resource/Models/matBall.obj");
	Dai::Shader *MyShader = new Dai::Shader();
	MyShader->attach("test.vert");
	MyShader->attach("test.frag");
	MyShader->link();

	Material *MyMaterial = new Material(MyShader, { {"diffuse", "/Resource/Textures/brushed_iron_01/2K/Albedo.png"} });

	GameObject *MyGameobject = new GameObject(MyMesh, MyMaterial);
	mGameObjects.push_back(MyGameobject);
}

void World::Render(Camera camera)
{
	for each (GameObject* obj in mGameObjects)
	{
		obj->Render(camera);
	}
}

