#pragma once

#include "Vertex.h"
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

#define INVALID_MATERIAL 0xFFFFFFFF

struct BoneInfo
{
	glm::mat4 BoneOffset;
	glm::mat4 FinalTransformation;

	BoneInfo()
	{
		/*BoneOffset.SetZero();
		FinalTransformation.SetZero();*/
	}
};

struct MeshEntry {
	MeshEntry()
	{
		NumIndices = 0;
		BaseVertex = 0;
		BaseIndex = 0;
		MaterialIndex = INVALID_MATERIAL;
	}

	unsigned int NumIndices;
	unsigned int BaseVertex;
	unsigned int BaseIndex;
	unsigned int MaterialIndex;
};

class Mesh
{
public:
	Mesh(char *path);
	~Mesh();

	// Test
	std::vector<VertexBoneData> bones;
	std::vector<MeshEntry> m_Entries;
	//vector<Texture*> m_Textures;

	std::map<std::string, uint16_t> m_BoneMapping; // maps a bone name to its index
	uint16_t m_NumBones;
	std::vector<BoneInfo> m_BoneInfo;
	glm::mat4 m_GlobalInverseTransform;

	const aiScene* m_pScene;
	Assimp::Importer m_Importer;

//	========

	std::vector<Vertex> GetVertices();
	std::vector<uint16_t> GetIndices();

	void* GetVertexBuffer();
	void* GetIndexBuffer();

protected:
	void* vertBuffer;
	void* indBuffer;

	bool hasNormalMap;

	std::vector<Vertex> verts;
	std::vector<uint16_t> indices;

private:
	void loadVertices(char *path);
	void CalculateTangents(Vertex*, uint16_t, uint16_t*, uint16_t);

	bool InitFromScene(const aiScene * pScene, const std::string & Filename);
	void InitMesh(uint16_t MeshIndex, const aiMesh * paiMesh, std::vector<Vertex>& vertices, std::vector<VertexBoneData>& Bones, std::vector<uint16_t>& Indices);
	void LoadBones(uint16_t MeshIndex, const aiMesh * pMesh, std::vector<VertexBoneData>& Bones);
};

