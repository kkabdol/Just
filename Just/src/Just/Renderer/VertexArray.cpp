#include "jstpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Just
{
	VertexArray * VertexArray::Create()
	{
		switch( Renderer::GetAPI() )
		{
		case RendererAPI::API::None:
			JST_CORE_ASSERT( false, "RendererAPI::API::None is currently not supported!" );
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		JST_CORE_ASSERT( false, "Unknown RendererAPI!" );
		return nullptr;
	}
}

