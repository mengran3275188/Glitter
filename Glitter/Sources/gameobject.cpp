#include "gameobject.hpp"


GameObject::GameObject(Dai::Mesh* mesh, Material* material) : mMesh(mesh), mMaterial(material)
{
}

void GameObject::Render(Camera &camera)
{
	mMaterial->Activate(camera);
	mMesh->draw(mMaterial->GetShader());
}
