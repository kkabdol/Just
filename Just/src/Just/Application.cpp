#include "jstpch.h"
#include "Application.h"

#include "Just/Events/ApplicationEvent.h"

#include <glad/glad.h>

namespace Just
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		JST_CORE_ASSERT( !s_Instance, "Application already exists!" );
		s_Instance = this;

		m_Window = std::unique_ptr< Window >( Window::Create() );
		m_Window->SetEventCallback( JST_BIND_EVENT_FN( Application::OnEvent ) );

		PushOverlay( new ImGuiLayer );
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

			for( Layer* layer : m_LayerStack )
			{
				layer->OnUpdate();
			}

			ImGuiLayer::Begin();
			for( Layer* layer : m_LayerStack )
			{
				layer->OnImGuiRender();
			}
			ImGuiLayer::End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent( Event & e )
	{
		EventDispatcher dispatcher( e );
		dispatcher.Dispatch< WindowCloseEvent >( JST_BIND_EVENT_FN( Application::OnWindowClose ) );

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