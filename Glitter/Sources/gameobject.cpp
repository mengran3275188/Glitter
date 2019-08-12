#include "gameobject.hpp"


GameObject::GameObject(Dai::Mesh* mesh, Material* material) : mMesh(mesh), mMaterial(material)
{
}

void GameObject::SetIrradiance(GLuint texture)
{
	mIrradianceTexture = texture;
}

void GameObject::Render(Camera &camera)
{
	mMaterial->Activate(camera, mIrradianceTexture);
	mMesh->draw(mMaterial->GetShader());
}
