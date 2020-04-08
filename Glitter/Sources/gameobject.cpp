#include "gameobject.hpp"


GameObject::GameObject(Dai::Mesh* mesh, Material* material) : mMesh(mesh), mMaterial(material)
{
}

void GameObject::SetIrradiance(GLuint texture)
{
	mIrradianceTexture = texture;
}

void GameObject::SetPos(glm::vec3 inPos)
{
	mPos = inPos;
}

void GameObject::SetScale(glm::vec3 inScale)
{
	mScale = inScale;
}

void GameObject::Render(Camera &camera, Material* overrideMat)
{
	if(overrideMat)
	{
		overrideMat->Activate(camera, mIrradianceTexture, mPos, mScale);
		mMesh->draw(overrideMat->GetShader());
	}
	else
	{
		mMaterial->Activate(camera, mIrradianceTexture, mPos, mScale);
		mMesh->draw(mMaterial->GetShader());
	}
}
