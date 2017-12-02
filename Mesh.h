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
		BoneOffset = glm::mat4(0.f);
		FinalTransformation = glm::mat4(0.f);
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
	
	// TODO: Encapsulation
	std::vector<MeshEntry> m_Entries;
	//vector<Texture*> m_Textures;

	bool hasAnimation = false;

	std::vector<glm::mat4> BoneTransforms;
	void BoneTransform(float TimeInSeconds);
	
	uint32_t getVertexSize();
	std::vector<uint16_t> GetIndices();

	void** GetVertexBuffer();
	void* GetIndexBuffer();

protected:
	void* vertBuffer;
	void* indBuffer;

	void* verts;

	unsigned int NumVertices = 0;
	unsigned int NumIndices = 0;

	uint32_t vertexSize;

	std::vector<uint16_t> indices;

private:
	const aiScene* m_pScene;
	Assimp::Importer m_Importer;

	std::map<std::string, uint16_t> m_BoneMapping; // maps a bone name to its index
	uint16_t m_NumBones;
	std::vector<BoneInfo> m_BoneInfo;

	uint32_t CalculateVertexSize() const;

	float AnimationTime = 0.f;

	bool InitFromScene(const aiScene * pScene, const std::string & Filename);
	void InitMeshes(const aiScene* pScene);
	void LoadBones(unsigned int MeshIndex, const aiMesh * pMesh);

	bool InitMaterials(const aiScene * pScene, const std::string & Filename);

	void ReadNodeHeirarchy(float AnimationTime, const aiNode * pNode, const glm::mat4 & ParentTransform);
	const aiNodeAnim * FindNodeAnim(const aiAnimation * pAnimation, const std::string NodeName);

	unsigned int FindPosition(float AnimationTime, const aiNodeAnim * pNodeAnim);
	unsigned int FindRotation(float AnimationTime, const aiNodeAnim * pNodeAnim);
	unsigned int FindScaling(float AnimationTime, const aiNodeAnim * pNodeAnim);

	void CalcInterpolatedPosition(aiVector3D & Out, float AnimationTime, const aiNodeAnim * pNodeAnim);
	void CalcInterpolatedRotation(aiQuaternion & Out, float AnimationTime, const aiNodeAnim * pNodeAnim);
	void CalcInterpolatedScaling(aiVector3D & Out, float AnimationTime, const aiNodeAnim * pNodeAnim);
};

