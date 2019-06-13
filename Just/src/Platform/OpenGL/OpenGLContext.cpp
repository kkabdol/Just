#include "jstpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace Just
{

	OpenGLContext::OpenGLContext( GLFWwindow* windowHandle )
		: m_WindowHandle( windowHandle )
	{
		JST_CORE_ASSERT( windowHandle, "Window handle is null!" );
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent( m_WindowHandle );
		int status = gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress );
		JST_CORE_ASSERT( status, "Failed to initialize glad!" );
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers( m_WindowHandle );
	}
}