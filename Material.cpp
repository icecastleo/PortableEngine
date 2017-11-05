#include "Material.h"

Material::Material()
{

#if _PC
	// d3d11
#endif

#if _PS4
	// PS4 Resource Manager or Material Manager
#endif

}


Material::~Material()
{
}

void Material::UseTransperancy(bool  _usesTrans) {
	usesTrans = _usesTrans;
}
bool Material::HasNormalMap() {
	return hasNormal;
}
bool Material::UseTransperancy() {
	return usesTrans;
}

void Material::setNormalPath(const wchar_t* path) {
	normalPath = path;
}

