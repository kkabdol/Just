#include "jstpch.h"
#include "Application.h"

#include "Just/Events/ApplicationEvent.h"

#include <glad/glad.h>

namespace Just
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		JST_CORE_ASSERT( !s_Instance, "Application already exists!" );
		s_Instance = this;

		m_Window = std::unique_ptr< Window >( Window::Create() );
		m_Window->SetEventCallback( BIND_EVENT_FN( OnEvent ) );
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while( m_Running )
		{
			glClearColor( 1, 0, 1, 1 );
			glClear( GL_COLOR_BUFFER_BIT );

			for( auto it = m_LayerStack.begin(); it != m_LayerStack.end(); ++it )
			{
				( *it )->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent( Event & e )
	{
		EventDispatcher dispatcher( e );
		dispatcher.Dispatch< WindowCloseEvent >( BIND_EVENT_FN( OnWindowClose ) );

		JST_CORE_TRACE( "{0}", e );

		for( auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			( *--it )->OnEvent( e );
			if( e.handled )
			{
				break;
			}
		}
	}

	void Application::PushLayer( Layer * layer )
	{
		m_LayerStack.PushLayer( layer );
		layer->OnAttach();
	}

	void Application::PushOverlay( Layer * layer )
	{
		m_LayerStack.PushOverlay( layer );
		layer->OnAttach();
	}

	bool Application::OnWindowClose( WindowCloseEvent & e )
	{
		m_Running = false;
		return true;
	}
}