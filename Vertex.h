#pragma once

#include "glm\glm.hpp"

#define kVertexMaxBoneWeight 4

struct Vertex
{
	glm::vec3 Position;	    // The position of the vertex
	glm::vec2 UV;			// UV location
	glm::vec3 Normal;		// Normal direction
	glm::vec3 Tangent;		// For normal mapping
};

struct VertexBoneData
{
	uint32_t ids[kVertexMaxBoneWeight];
	float weights[kVertexMaxBoneWeight];

	VertexBoneData()
	{
		Reset();
	};

	void Reset()
	{
		memset(&ids, 0, sizeof(uint32_t) * kVertexMaxBoneWeight);
		memset(&weights, 0, sizeof(float) * kVertexMaxBoneWeight);
	}

	void AddBoneData(uint32_t BoneID, float Weight) {
		for (uint32_t i = 0; i < kVertexMaxBoneWeight; i++) {
			if (weights[i] == 0.0) {
				ids[i] = BoneID;
				weights[i] = Weight;
				return;
			}
		}

		// should never get here - more bones than we have space for
		assert(0);
	}
};


//struct SkinnedVertex
//{
//	glm::vec3 Position;	    // The position of the vertex
//	glm::vec2 UV;			// UV location
//	glm::vec3 Normal;		// Normal direction
//	glm::vec3 Tangent;		// For normal mapping
//
//	float ids[kVertexMaxBoneWeight];
//	float weights[kVertexMaxBoneWeight];
//
//	SkinnedVertex()
//	{
//		Reset();
//	};
//
//	void Reset()
//	{
//		memset(&ids, 0, sizeof(float) * kVertexMaxBoneWeight);
//		memset(&weights, 0, sizeof(float) * kVertexMaxBoneWeight);
//	}
//
//	void AddBoneData(uint16_t BoneID, float Weight) {
//		for (uint16_t i = 0; i < kVertexMaxBoneWeight; i++) {
//			if (weights[i] == 0.0) {
//				ids[i] = BoneID;
//				weights[i] = Weight;
//				return;
//			}
//		}
//
//		// should never get here - more bones than we have space for
//		assert(0);
//	}
//};

enum VertexElements
{
	kVertexPosition = 0,
	kVertexUv,
	kVertexNormal,
	kVertexTangent,
	kVertexElemCount
};