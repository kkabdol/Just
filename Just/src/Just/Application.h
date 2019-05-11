#pragma once

#include "Just/Core.h"
#include "Just/Window.h"
#include "Just/Events/ApplicationEvent.h"

namespace Just
{
	class JUST_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent( Event& e );
	private:
		bool OnWindowClose( WindowCloseEvent& e );

		std::unique_ptr< Window > m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

