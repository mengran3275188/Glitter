#pragma once

// Standard Headers
#include <vector>
#include "shader.hpp";

// Local Headers
#include "gameobject.hpp"
#include "camera.hpp"

class World
{
public:
	void Init();
	void Render(Camera camera);

private:
	GLuint LoadCubemap(std::vector<std::string> faces);
	void DrawSkybox(Camera camera);
	void RenderSphere();

	std::vector<GameObject*> mGameObjects;
	std::vector<GameObject*> mLights;

	GLuint mSkyboxVAO;
	GLuint mSkyboxTexture;
	Dai::Shader *mSkyboxShader;
	Dai::Shader *mPbrShader;
};
