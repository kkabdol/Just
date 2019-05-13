#pragma once

#include "Just/Core.h"

#include "Just/Window.h"
#include "Just/LayerStack.h"
#include "Just/Events/ApplicationEvent.h"

#pragma warning( push )
#pragma warning( disable : 4251 )
namespace Just
{
	template class JUST_API std::unique_ptr< Window >;

	class JUST_API Application
	{
	
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent( Event& e );

		void PushLayer( Layer* layer );
		void PushOverlay( Layer* layer );
	private:
		bool OnWindowClose( WindowCloseEvent& e );

		std::unique_ptr< Window > m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
#pragma warning( pop )