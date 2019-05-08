#include "jstpch.h"
#include "Application.h"

#include "Just/Events/ApplicationEvent.h"
#include "Just/Log.h"

namespace Just
{

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e( 1280, 720 );
		if( e.IsInCategory( EventCategoryApplication ) )
		{
			JST_TRACE( e );
		}
		if( e.IsInCategory( EventCategoryInput ) )
		{
			JST_WARN( e );
		}

		while( true );
	}
}