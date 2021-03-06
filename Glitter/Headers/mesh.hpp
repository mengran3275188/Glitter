#pragma once

// System Headers
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

// Preprocessor Directives

// Standard Headers
#include <map>
#include <memory>
#include <vector>

namespace Dai
{
	// Vertex Format
	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
	};

	class Mesh
	{
	public:
		// Implement Default Constructor and Destructor
		Mesh() { glGenVertexArrays(1, &mVertexArray); }
		~Mesh() { glDeleteVertexArrays(1, &mVertexArray); }

		// Implement Custom Constructions;
		Mesh(std::string const & filename);
		Mesh(std::vector<Vertex> const & vertices,
			std::vector<GLuint> const & indices,
			std::map<GLuint, std::string> const & textures);

		void draw(GLuint shader);

	private:

		// Disable Copying and Assignment
		Mesh(Mesh const &) = delete;
		Mesh& operator =(Mesh const &) = delete;

		// Private Member Functions
		void parse(std::string const & path, aiNode const * node, aiScene const * scene);
		void parse(std::string const & path, aiMesh const * mesh, aiScene const * scene);
		std::map<GLuint, std::string> process(std::string const & path,
			aiMaterial * material,
			aiTextureType type);

		// Private Member Containers
		std::vector<std::unique_ptr<Mesh>> mSubMeshes;
		std::vector<GLuint> mIndices;
		std::vector<Vertex> mVertices;
		std::map<GLuint, std::string> mTextures;

		// Private Member Variable
		GLuint mVertexArray;
		GLuint mVertexBuffer;
		GLuint mElementBuffer;
	};
}

