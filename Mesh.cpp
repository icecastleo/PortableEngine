#define GLM_FORCE_SWIZZLE

#include "Mesh.h"
#include <assimp/DefaultLogger.hpp>
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\quaternion.hpp"
#include <string>

using namespace std;
using namespace glm;
using namespace Assimp;

// Private functions to convert from Assimp data types to glm
static glm::vec3 aiToGlm(const aiVector3D& v)
{
	glm::vec3 out;
	assert(sizeof(out) == sizeof(v));
	memcpy(&out, &v, sizeof(v));
	return out;
}

static glm::quat aiToGlm(const aiQuaternion& v)
{
	return glm::quat(v.w, v.x, v.y, v.z);
}

static glm::mat4 aiToGlm(const aiMatrix4x4& v)
{
	glm::mat4 out;
	assert(sizeof(out) == sizeof(v));
	memcpy(&out, &v, sizeof(v));
	return glm::transpose(out);
}

Mesh::Mesh(char *path)
{
	BoneTransforms.resize(0);

	// Create a logger instance
	DefaultLogger::create("", Logger::VERBOSE);
	// Now I am ready for logging my stuff
	DefaultLogger::get()->info("this is my info-call");
	// Kill it after the work is done
	
	if (strcmp(path, "Assets/Models/test.obj") == 0) {
		path = "Assets/Models/Spider_3.fbx";
	}

	m_pScene = m_Importer.ReadFile(path,
		aiProcess_Triangulate | aiProcess_ConvertToLeftHanded | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace
		| aiProcess_LimitBoneWeights | aiProcess_ValidateDataStructure);

	// Check for errors
	if (!m_pScene || m_pScene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !m_pScene->mRootNode) // if is Not Zero
	{
		char buffer[500];
		sprintf_s(buffer, "ERROR::ASSIMP:: %s \n", m_Importer.GetErrorString());
		perror(buffer);
		return;
	}

	InitFromScene(m_pScene, string(path));

	DefaultLogger::kill();

	return;
}

Mesh::~Mesh() {
	free(verts);
}

bool Mesh::InitFromScene(const aiScene* pScene, const string& Filename)
{
	m_Entries.resize(pScene->mNumMeshes);
	//m_Textures.resize(pScene->mNumMaterials);

	if (m_pScene->mAnimations) {
		hasAnimation = true;
	}
	vertexSize = CalculateVertexSize();

	// Count the number of vertices and indices
	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		m_Entries[i].BaseVertex = NumVertices;
		m_Entries[i].BaseIndex = NumIndices;
		m_Entries[i].NumIndices = pScene->mMeshes[i]->mNumFaces * 3;
		m_Entries[i].MaterialIndex = pScene->mMeshes[i]->mMaterialIndex;
		
		NumVertices += pScene->mMeshes[i]->mNumVertices;
		NumIndices += m_Entries[i].NumIndices;
	}

	// Reserve space in the vectors for the vertex attributes and indices
	verts = malloc(vertexSize * NumVertices);
	indices.reserve(NumIndices);
	
	// Initialize the meshes in the scene
	InitMeshes(pScene);

	/*if (!InitMaterials(pScene, Filename)) {
		return false;
	}*/

	return true;
}

uint32_t Mesh::CalculateVertexSize() const
{
	uint32_t vertexSize = sizeof(Vertex);

	if (hasAnimation == 1)
	{
		vertexSize += sizeof(VertexBoneData); // bone ids + bone weights
	}

	return vertexSize;
}

void Mesh::InitMeshes(const aiScene* pScene)
{
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	Vertex *vertex = reinterpret_cast<Vertex*>(verts);
	VertexBoneData *bone;

	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < m_Entries.size(); i++) {
		const aiMesh* paiMesh = pScene->mMeshes[i];

		// Populate the vertex attribute vectors
		for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
			vertex = new(vertex) Vertex();
			vertex->Position = aiToGlm(paiMesh->mVertices[i]);
			vertex->UV = aiToGlm(paiMesh->HasTextureCoords(0) ? paiMesh->mTextureCoords[0][i] : Zero3D).xy;
			vertex->Normal = aiToGlm(paiMesh->mNormals[i]);
			vertex->Tangent = aiToGlm(paiMesh->mTangents[i]);

			vertex += 1;

			// reserve space for bone info
			if (hasAnimation) {
				bone = new(vertex) VertexBoneData();
				vertex = reinterpret_cast<Vertex*>(bone + 1);
			}
		}

		if (hasAnimation) {
			LoadBones(i, paiMesh);
		}

		// Populate the index buffer
		for (unsigned int j = 0; j < paiMesh->mNumFaces; j++) {
			const aiFace& Face = paiMesh->mFaces[j];
			assert(Face.mNumIndices == 3);
			indices.push_back(Face.mIndices[0] + m_Entries[i].BaseVertex);
			indices.push_back(Face.mIndices[1] + m_Entries[i].BaseVertex);
			indices.push_back(Face.mIndices[2] + m_Entries[i].BaseVertex);
		}
	}
}

void Mesh::LoadBones(unsigned int MeshIndex, const aiMesh* pMesh)
{
	for (unsigned int i = 0; i < pMesh->mNumBones; i++) {
		unsigned int BoneIndex = 0;
		string BoneName(pMesh->mBones[i]->mName.data);

		if (m_BoneMapping.find(BoneName) == m_BoneMapping.end()) {
			// Allocate an index for a new bone
			BoneIndex = m_NumBones;
			m_NumBones++;
			BoneInfo bi;
			m_BoneInfo.push_back(bi);

			m_BoneInfo[BoneIndex].BoneOffset = aiToGlm(pMesh->mBones[i]->mOffsetMatrix);
			m_BoneMapping[BoneName] = BoneIndex;
		}
		else {
			BoneIndex = m_BoneMapping[BoneName];
		}
		
		VertexBoneData *bone;

		for (unsigned int j = 0; j < pMesh->mBones[i]->mNumWeights; j++) {
			unsigned int VertexID = m_Entries[MeshIndex].BaseVertex + pMesh->mBones[i]->mWeights[j].mVertexId;
			float Weight = pMesh->mBones[i]->mWeights[j].mWeight;

			bone = reinterpret_cast<VertexBoneData*>((char*)verts + VertexID * vertexSize + sizeof(Vertex));
			bone->AddBoneData(BoneIndex, Weight);
		}
	}
}

bool Mesh::InitMaterials(const aiScene* pScene, const string& Filename)
{
	// Extract the directory part from the file name
	string::size_type SlashIndex = Filename.find_last_of("/");
	string Dir;

	if (SlashIndex == string::npos) {
		Dir = ".";
	}
	else if (SlashIndex == 0) {
		Dir = "/";
	}
	else {
		Dir = Filename.substr(0, SlashIndex);
	}

	bool Ret = true;

	// Initialize the materials
	for (uint i = 0; i < pScene->mNumMaterials; i++) {
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		//m_Textures[i] = NULL;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				string p(Path.data);

				if (p.substr(0, 2) == ".\\") {
					p = p.substr(2, p.size() - 2);
				}

				string FullPath = Dir + "/" + p;

				/*m_Textures[i] = new Texture(GL_TEXTURE_2D, FullPath.c_str());

				if (!m_Textures[i]->Load()) {
					printf("Error loading texture '%s'\n", FullPath.c_str());
					delete m_Textures[i];
					m_Textures[i] = NULL;
					Ret = false;
				}
				else {
					printf("%d - loaded texture '%s'\n", i, FullPath.c_str());
				}*/
			}
		}
	}
	return Ret;
}

void Mesh::BoneTransform(float TimeInSeconds)
{
	if (!hasAnimation)
		return;

	AnimationTime += TimeInSeconds;

	float TicksPerSecond = m_pScene->mAnimations[0]->mTicksPerSecond != 0 ?
		m_pScene->mAnimations[0]->mTicksPerSecond : 25.0f;
	float TimeInTicks = AnimationTime * TicksPerSecond;
	float AnimationTime = fmod(TimeInTicks, m_pScene->mAnimations[0]->mDuration);

	ReadNodeHeirarchy(AnimationTime, m_pScene->mRootNode, mat4(1.0f));

	// FIXME: size constant
	BoneTransforms.resize(100);

	// TODO: Memcpy
	for (unsigned int i = 0; i < m_NumBones; i++) {
		BoneTransforms[i] = transpose(m_BoneInfo[i].FinalTransformation);
	}
}

void Mesh::ReadNodeHeirarchy(float AnimationTime, const aiNode* pNode, const mat4& ParentTransform)
{
	string NodeName(pNode->mName.data);

	const aiAnimation* pAnimation = m_pScene->mAnimations[0];

	mat4 NodeTransformation = aiToGlm(pNode->mTransformation);

	const aiNodeAnim* pNodeAnim = FindNodeAnim(pAnimation, NodeName);

	if (pNodeAnim) {
		mat4 local = mat4(1.0f);

		// Interpolate scaling and generate scaling transformation matrix
		aiVector3D Scaling;
		CalcInterpolatedScaling(Scaling, AnimationTime, pNodeAnim);
		mat4 ScalingM = scale(local, aiToGlm(Scaling));
	
		// Interpolate rotation and generate rotation transformation matrix
		aiQuaternion RotationQ;
		CalcInterpolatedRotation(RotationQ, AnimationTime, pNodeAnim);
		mat4 RotationM = toMat4(aiToGlm(RotationQ));

		// Interpolate translation and generate translation transformation matrix
		aiVector3D Translation;
		CalcInterpolatedPosition(Translation, AnimationTime, pNodeAnim);
		mat4 TranslationM = translate(local, aiToGlm(Translation));
		
		// Combine the above transformations
		NodeTransformation = TranslationM * RotationM * ScalingM;
	}

	mat4 GlobalTransformation = ParentTransform * NodeTransformation;

	if (m_BoneMapping.find(NodeName) != m_BoneMapping.end()) {
		unsigned int BoneIndex = m_BoneMapping[NodeName];
		m_BoneInfo[BoneIndex].FinalTransformation = GlobalTransformation * m_BoneInfo[BoneIndex].BoneOffset;
	}

	for (unsigned int i = 0; i < pNode->mNumChildren; i++) {
		ReadNodeHeirarchy(AnimationTime, pNode->mChildren[i], GlobalTransformation);
	}
}

const aiNodeAnim* Mesh::FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
{
	for (unsigned int i = 0; i < pAnimation->mNumChannels; i++) {
		const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

		if (string(pNodeAnim->mNodeName.data) == NodeName) {
			return pNodeAnim;
		}
	}

	return NULL;
}

unsigned int Mesh::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);
	return 0;
}

unsigned int Mesh::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumRotationKeys > 0);

	for (unsigned int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);
	return 0;
}

unsigned int Mesh::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumScalingKeys > 0);

	for (unsigned int i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);
	return 0;
}

void Mesh::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumPositionKeys == 1) {
		Out = pNodeAnim->mPositionKeys[0].mValue;
		return;
	}

	unsigned int PositionIndex = FindPosition(AnimationTime, pNodeAnim);
	unsigned int NextPositionIndex = (PositionIndex + 1);
	assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
	float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
	const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
	aiVector3D Delta = End - Start;
	Out = Start + Factor * Delta;
}

void Mesh::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	// we need at least two values to interpolate...
	if (pNodeAnim->mNumRotationKeys == 1) {
		Out = pNodeAnim->mRotationKeys[0].mValue;
		return;
	}

	unsigned int RotationIndex = FindRotation(AnimationTime, pNodeAnim);
	unsigned int NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
	float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
	const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
	aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
	Out = Out.Normalize();
}

void Mesh::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumScalingKeys == 1) {
		Out = pNodeAnim->mScalingKeys[0].mValue;
		return;
	}

	unsigned int ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
	unsigned int NextScalingIndex = (ScalingIndex + 1);
	assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
	float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
	float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
	const aiVector3D& End = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
	aiVector3D Delta = End - Start;
	Out = Start + Factor * Delta;
}

uint32_t Mesh::getVertexSize()
{
	return vertexSize;
}

std::vector<uint16_t> Mesh::GetIndices()
{
	return indices;
}

void** Mesh::GetVertexBuffer()
{
	return &vertBuffer;
}

void* Mesh::GetIndexBuffer()
{
	return indBuffer;
}