#include "jstpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Just
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}