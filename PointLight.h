#pragma once
#include <string>
#include <glm/vec3.hpp> // glm::vec3
#include "Shader.h"
#include <memory>

namespace OpenGLEntity {
	class PointLight
	{
	public:
		static std::shared_ptr<PointLight> create(GLProgramPtr program, std::string name);

	private:
		std::string entityName;
		GLProgramPtr program;

	public:
		PointLight(GLProgramPtr program, std::string name);
		~PointLight();

		void setPosition(float x, float y, float z);
		void setAmbient(float x, float y, float z);
		void setDiffuse(float x, float y, float z);
		void setSpecular(float x, float y, float z);
		void setConstant(float constant);
		void setLinear(float linear);
		void setQuadratic(float quadratic);
	};
}



