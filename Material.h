#pragma once
class Material
{
protected:
	bool usesTrans;
	bool hasNormal;
	
public:
	Material();
	virtual ~Material();

	void UseTransperancy(bool);
	bool HasNormalMap();
	bool UseTransperancy();
};

