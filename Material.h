#pragma once
#include"shader.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
class Material
{
public:
	unsigned int diffuse;
	unsigned int specular;
	unsigned int emissionMap;
	float shininess;
	enum Slot
	{
		DIFFUSE,
		SPECULAR,
		EMISSIONMAP
	};
	Material( unsigned int _diffuse, unsigned int _specular, float _shininess) :
		 diffuse(_diffuse),specular(_specular), shininess(_shininess)
	{
		emissionMap = 0;
	}
	void setEmissionMap(unsigned int _emissionMap)
	{
		emissionMap = _emissionMap;
	}
	~Material() {}

};


