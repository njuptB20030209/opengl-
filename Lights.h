#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
class Light
{
public:
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Light(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular, glm::vec3 _postion) :
		ambient(_ambient), diffuse(_diffuse), specular(_specular), position(_postion)
	{
		color = glm::vec3(1.0f);
	};
	Light() {};
	void setPos(glm::vec3 _postion)
	{
		position = _postion;
	}
	void setColor(glm::vec3 _color)
	{
		color = _color;
	}
	void setDiffuse(glm::vec3 _diffuse)
	{
		diffuse = _diffuse;
	}
	void setSpecular(glm::vec3 _specular)
	{
		specular = _specular;
	}
	void setAmbient(glm::vec3 _ambient)
	{
		ambient = _ambient;
	}
};

class DirLight : public Light
{
public:
	glm::vec3 direction;

	DirLight(Light light, glm::vec3 _direction):Light(light), direction(_direction){}
	
	void setDirection(glm::vec3 _direction)
	{
		direction = _direction;
	}
private:
};
class PointLight : public Light
{
public:
	glm::vec3 attenuation;

	PointLight(Light light, glm::vec3 _attenuation) :Light(light), attenuation(_attenuation) {}
	
	PointLight():Light(glm::vec3(0.05f), glm::vec3(0.8f), glm::vec3(1.0f), glm::vec3(1.2f, 1.0f, 2.0f)),attenuation(glm::vec3(1.0f, 0.07f, 0.017f))
	{
		//仅作特殊用途,构造数组
	}
	void setAttenuation(glm::vec3 _attenuation)
	{
		attenuation = _attenuation;
	}
};
class SpotLight : public Light
{
public:
	glm::vec3 direction;
	glm::vec3 attenuation;
	float cutOff;
	float outerCutOff;

	SpotLight(Light light, glm::vec3 _direction, glm::vec3 _attenuation,float _cutOff, float _outerCutOff):
		Light(light), direction(_direction), attenuation(_attenuation), cutOff(_cutOff), outerCutOff(_outerCutOff)
	{}
	void setDirection(glm::vec3 _direction)
	{
		direction = _direction;
	}
	void setAttenuation(glm::vec3 _attenuation)
	{
		attenuation = _attenuation;
	}
	void setCutOff(float _cutOff)
	{
		cutOff = _cutOff;
	}
	void setOuterCutOff(float _outerCutOff)
	{
		outerCutOff = _outerCutOff;
	}
};