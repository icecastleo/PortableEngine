#pragma once

// TODO: Skybox material class?
enum MaterialType { kMaterialNormal, kMaterialCubemap };

// TODO: Add shaders

class Material
{
protected:
	void* normalSRV;
	bool usesTrans = false;

public:
	Material();
	virtual ~Material();

	// TODO: private?
	MaterialType type;

	void* GetNormalSRV();

	void UseTransperancy(bool);
	bool HasNormalMap();
	bool UseTransperancy();
};

