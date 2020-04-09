#include "SpotLight.h"

namespace OpenGLEntity {


	std::shared_ptr<SpotLight> OpenGLEntity::SpotLight::create(GLProgramPtr program, std::string name)
	{
		return std::make_shared<SpotLight>(program, name);
	}

	OpenGLEntity::SpotLight::SpotLight(GLProgramPtr program, std::string name)
	{
		this->program = program;
		this->entityName = name;
	}

	OpenGLEntity::SpotLight::~SpotLight()
	{
		program = nullptr;
		entityName = nullptr;
	}

	void OpenGLEntity::SpotLight::setPosition(float x, float y, float z)
	{
		program->use();
		program->setVec3(entityName + ".position", x, y, z);
	}

	void OpenGLEntity::SpotLight::setDirection(float x, float y, float z)
	{
		program->use();
		program->setVec3(entityName + ".direction", x, y, z);
	}

	void OpenGLEntity::SpotLight::setAmbient(float x, float y, float z)
	{
		program->use();
		program->setVec3(entityName + ".ambient", x, y, z);
	}

	void OpenGLEntity::SpotLight::setDiffuse(float x, float y, float z)
	{
		program->use();
		program->setVec3(entityName + ".diffuse", x, y, z);
	}

	void OpenGLEntity::SpotLight::setSpecular(float x, float y, float z)
	{
		program->use();
		program->setVec3(entityName + ".specular", x, y, z);
	}

	void OpenGLEntity::SpotLight::setConstant(float constant)
	{
		program->use();
		program->setFloat(entityName + ".constant", constant);
	}

	void OpenGLEntity::SpotLight::setLinear(float linear)
	{
		program->use();
		program->setFloat(entityName + ".linear", linear);
	}

	void OpenGLEntity::SpotLight::setQuadratic(float quadratic)
	{
		program->use();
		program->setFloat(entityName + ".quadratic", quadratic);
	}

	void OpenGLEntity::SpotLight::setCutOff(float cutOff)
	{
		program->use();
		program->setFloat(entityName + ".cutOff", cutOff);
	}

	void OpenGLEntity::SpotLight::setOuterCutOff(float outerCutOff)
	{
		program->use();
		program->setFloat(entityName + ".outerCutOff", outerCutOff);
	}

}

