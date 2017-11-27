#include "Animation.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\quaternion.hpp"
#include <algorithm> 

using namespace glm;

Keyframe::Keyframe()
	: TimePos(0.0f),
	Translation(0.0f, 0.0f, 0.0f),
	Scale(1.0f, 1.0f, 1.0f),
	RotationQuat(0.0f, 0.0f, 0.0f, 1.0f)
{
}

Keyframe::~Keyframe()
{
}

float BoneAnimation::GetStartTime()const
{
	// Keyframes are sorted by time, so first keyframe gives start time.
	return Keyframes.front().TimePos;
}

float BoneAnimation::GetEndTime()const
{
	// Keyframes are sorted by time, so last keyframe gives end time.
	float f = Keyframes.back().TimePos;

	return f;
}

BoneAnimation::BoneAnimation()
{
	quat q0 = angleAxis(30.0f, vec3(0.0f, 1.0f, 0.0f));
	quat q1 = angleAxis(45.0f, vec3(1.0f, 1.0f, 2.0f));
	quat q2 = angleAxis(-30.0f, vec3(0.0f, 1.0f, 0.0f));
	quat q3 = angleAxis(70.0f, vec3(1.0f, 0.0f, 0.0f));

	Keyframes.resize(5);
	Keyframes[0].TimePos = 0.0f;
	Keyframes[0].Translation = vec3(-3.0f, 0.0f, 0.0f);
	Keyframes[0].Scale = vec3(0.5f, 0.5f, 0.5f);
	Keyframes[0].RotationQuat = q0;
	
	Keyframes[1].TimePos = 2.0f;
	Keyframes[1].Translation = vec3(0.0f, 2.0f, 10.0f);
	Keyframes[1].Scale = vec3(1.0f, 1.0f, 1.0f);
	Keyframes[1].RotationQuat = q1;

	Keyframes[2].TimePos = 4.0f;
	Keyframes[2].Translation = vec3(3.0f, 0.0f, 0.0f);
	Keyframes[2].Scale = vec3(0.5f, 0.5f, 0.5f);
	Keyframes[2].RotationQuat = q2;

	Keyframes[3].TimePos = 6.0f;
	Keyframes[3].Translation = vec3(0.0f, 1.0f, -10.0f);
	Keyframes[3].Scale = vec3(1.0f, 1.0f, 1.0f);
	Keyframes[3].RotationQuat = q3;

	Keyframes[4].TimePos = 8.0f;
	Keyframes[4].Translation = vec3(-3.0f, 0.0f, 0.0f);
	Keyframes[4].Scale = vec3(0.5f, 0.5f, 0.5f);
	Keyframes[4].RotationQuat = q0;
}

void BoneAnimation::Interpolate(float t, mat4& M)const
{
	// t is before the animation started, so just return the first key frame.
	if (t <= Keyframes.front().TimePos)
	{
		mat4 local = mat4(1.0f);
		mat4 myTranslationMatrix = translate(local, Keyframes.front().Translation);
		mat4 myRotationMatrix = toMat4(Keyframes.front().RotationQuat);
		mat4 myScaleMatrix = scale(local, Keyframes.front().Scale);
		local = myTranslationMatrix * myRotationMatrix * myScaleMatrix;
		M = transpose(local);

	} 
	// t is after the animation ended, so just return the last key frame.
	else if (t >= Keyframes.back().TimePos)
	{
		mat4 local = mat4(1.0f);
		mat4 myTranslationMatrix = translate(local, Keyframes.back().Translation);
		mat4 myRotationMatrix = toMat4(Keyframes.back().RotationQuat);
		mat4 myScaleMatrix = scale(local, Keyframes.back().Scale);
		local = myTranslationMatrix * myRotationMatrix * myScaleMatrix;
		M = transpose(local);
	} 
	// t is between two key frames, so interpolate.
	else
	{
		for (size_t i = 0; i < Keyframes.size() - 1; ++i)
		{
			if (t >= Keyframes[i].TimePos && t <= Keyframes[i + 1].TimePos)
			{
				float lerpPercent = (t - Keyframes[i].TimePos) /
					(Keyframes[i + 1].TimePos - Keyframes[i].TimePos);

				vec3 scale = mix(Keyframes[i].Scale, Keyframes[i + 1].Scale, lerpPercent);
				vec3 translation = mix(Keyframes[i].Translation, Keyframes[i + 1].Translation, lerpPercent);
				quat rotation = mix(Keyframes[i].RotationQuat, Keyframes[i + 1].RotationQuat, lerpPercent);
				
				mat4 local = mat4(1.0f);
				local = translate(local, translation) * toMat4(rotation) * glm::scale(local, scale);
				M = transpose(local);
				break;
			}
		}
	}
}

float AnimationClip::GetClipStartTime()const
{
	// Find smallest start time over all bones in this clip.
	float t = std::numeric_limits<float>::infinity();
	for (size_t i = 0; i < BoneAnimations.size(); ++i)
	{
		t = std::min(t, BoneAnimations[i].GetStartTime());
	}

	return t;
}

float AnimationClip::GetClipEndTime()const
{
	// Find largest end time over all bones in this clip.
	float t = 0.0f;
	for (size_t i = 0; i < BoneAnimations.size(); ++i)
	{
		t = std::max(t, BoneAnimations[i].GetEndTime());
	}

	return t;
}

void AnimationClip::Interpolate(float t, std::vector<mat4>& boneTransforms)const
{
	for (size_t i = 0; i < BoneAnimations.size(); ++i)
	{
		BoneAnimations[i].Interpolate(t, boneTransforms[i]);
	}
}

float SkinnedData::GetClipStartTime(const std::string& clipName)const
{
	auto clip = mAnimations.find(clipName);
	return clip->second.GetClipStartTime();
}

float SkinnedData::GetClipEndTime(const std::string& clipName)const
{
	auto clip = mAnimations.find(clipName);
	return clip->second.GetClipEndTime();
}

size_t SkinnedData::BoneCount()const
{
	return mBoneHierarchy.size();
}

void SkinnedData::Set(std::vector<int>& boneHierarchy,
	std::vector<mat4>& boneOffsets,
	std::map<std::string, AnimationClip>& animations)
{
	mBoneHierarchy = boneHierarchy;
	mBoneOffsets = boneOffsets;
	mAnimations = animations;
}

void SkinnedData::GetFinalTransforms(const std::string& clipName, float timePos, std::vector<mat4>& finalTransforms)const
{
	size_t numBones = mBoneOffsets.size();

	std::vector<mat4> toParentTransforms(numBones);

	// Interpolate all the bones of this clip at the given time instance.
	auto clip = mAnimations.find(clipName);
	clip->second.Interpolate(timePos, toParentTransforms);

	//
	// Traverse the hierarchy and transform all the bones to the root space.
	//

	std::vector<mat4> toRootTransforms(numBones);

	// The root bone has index 0.  The root bone has no parent, so its toRootTransform
	// is just its local bone transform.
	toRootTransforms[0] = toParentTransforms[0];

	// Now find the toRootTransform of the children.
	for (size_t i = 1; i < numBones; ++i)
	{
		/*XMMATRIX toParent = XMLoadFloat4x4(&toParentTransforms[i]);

		int parentIndex = mBoneHierarchy[i];
		XMMATRIX parentToRoot = XMLoadFloat4x4(&toRootTransforms[parentIndex]);

		XMMATRIX toRoot = XMMatrixMultiply(toParent, parentToRoot);

		XMStoreFloat4x4(&toRootTransforms[i], toRoot);*/

		int parentIndex = mBoneHierarchy[i];
		toRootTransforms[i] = toRootTransforms[parentIndex] * toParentTransforms[i];
	}

	// Premultiply by the bone offset transform to get the final transform.
	for (size_t i = 0; i < numBones; ++i)
	{
	/*	XMMATRIX offset = XMLoadFloat4x4(&mBoneOffsets[i]);
		XMMATRIX toRoot = XMLoadFloat4x4(&toRootTransforms[i]);
		XMStoreFloat4x4(&finalTransforms[i], XMMatrixMultiply(offset, toRoot));*/

		finalTransforms[i] = toRootTransforms[i] * mBoneOffsets[i];
	}
}

Animation::Animation()
{
}


Animation::~Animation()
{
}
