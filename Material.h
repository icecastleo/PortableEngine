#pragma once
class Material
{
protected:
	bool usesTrans;
	bool hasNormal;
	const wchar_t* normalPath;
public:
	Material();
	~Material();

	void UseTransperancy(bool);
	bool HasNormalMap();
	bool UseTransperancy();

	void setNormalPath(const wchar_t* path);
};

