#include "PointLight.h"

namespace OpenGLEntity {
	std::shared_ptr<PointLight> OpenGLEntity::PointLight::create(GLProgramPtr program, std::string name)
	{
		return std::make_shared<PointLight>(program,name);
	}

	OpenGLEntity::PointLight::PointLight(GLProgramPtr program, std::string name)
	{
		this->program = program;
		this->entityName = name;
	}

	OpenGLEntity::PointLight::~PointLight()
	{
		this->entityName = nullptr;
	}

	void OpenGLEntity::PointLight::setPosition(float x, float y, float z)
	{
		program->use();
		program->setVec3(entityName + ".position", x, y, z);
	}

	void OpenGLEntity::PointLight::setAmbient(float x, float y, float z)
	{
		program->use();
		program->setVec3(entityName + ".ambient", x, y, z);
	}

	void OpenGLEntity::PointLight::setDiffuse(float x, float y, float z)
	{
		program->use();
		program->setVec3(entityName + ".diffuse", x, y, z);
	}

	void OpenGLEntity::PointLight::setSpecular(float x, float y, float z)
	{
		program->use();
		program->setVec3(entityName + ".specular", x, y, z);
	}

	void OpenGLEntity::PointLight::setConstant(float constant)
	{
		program->use();
		program->setFloat(entityName + ".constant", constant);
	}

	void OpenGLEntity::PointLight::setLinear(float linear)
	{
		program->use();
		program->setFloat(entityName + ".linear", linear);
	}

	void OpenGLEntity::PointLight::setQuadratic(float quadratic)
	{
		program->use();
		program->setFloat(entityName + ".quadratic", quadratic);
	}
}


