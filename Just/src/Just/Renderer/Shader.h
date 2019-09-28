#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Just 
{
	class Shader
	{
	public:
		Shader( const std::string& vertexSrc, const std::string& fragmentSrc );
		~Shader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformMat4( const std::string& name, const glm::mat4& matrix );
	private:
		uint32_t m_Program;
	};
}