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
	void CaptureCubemap();

private:
	GLuint LoadCubemap(std::vector<std::string> faces);
	GLuint LoadHDR(std::string filepath);
	void DrawSkybox(Camera camera);
	void RenderSphere();
	void RenderCube();

	std::vector<GameObject*> mGameObjects;
	std::vector<GameObject*> mLights;

	GLuint mSkyboxVAO;
	GLuint mSkyboxTexture;
	GLuint mIrradianceTexture;
	GLuint mHdrTexture;
	GLuint mEnvCubeMap;

	GLuint mCubeVAO;
	GLuint mCubeVBO;
	Dai::Shader *mSkyboxShader;
	Dai::Shader *mBackgroundShader;
	Dai::Shader *mPbrShader;
	Dai::Shader *mEquirectangularToCubemapShader;

	int mCaptureSize = 2048;
};
