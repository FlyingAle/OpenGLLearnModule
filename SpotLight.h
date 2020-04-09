#pragma once
#include <string>
#include <glm/vec3.hpp> // glm::vec3
#include "Shader.h"
#include <memory>


namespace OpenGLEntity {

	class SpotLight
	{
	public:
		static std::shared_ptr<SpotLight> create(GLProgramPtr program, std::string name);
	private:
		GLProgramPtr program;
		std::string entityName;

	public:
		SpotLight(GLProgramPtr program,std::string name);
		~SpotLight();

		void setPosition(float x, float y, float z);

		void setDirection(float x, float y, float z);

		void setAmbient(float x, float y, float z);

		void setDiffuse(float x, float y, float z);

		void setSpecular(float x, float y, float z);

		void setConstant(float constant);

		void setLinear(float linear);

		void setQuadratic(float quadratic);

		void setCutOff(float cutOff);

		void setOuterCutOff(float outerCutOff);
	};

	typedef std::shared_ptr<SpotLight> SpotLightPtr;
}



