#pragma once

#include "Just/Core.h"

#include "Just/Window.h"
#include "Just/LayerStack.h"
#include "Just/Events/ApplicationEvent.h"

#include "Just/ImGui/ImGuiLayer.h"

#include "Just/Renderer/Shader.h"
#include "Just/Renderer/Buffer.h"
#include "Just/Renderer/VertexArray.h"

#include "Just/Renderer/OrthographicCamera.h"

#pragma warning( push )
#pragma warning( disable : 4251 )
namespace Just
{
	template class JUST_API std::unique_ptr< Window >;

	class JUST_API Application
	{
	
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent( Event& e );

		void PushLayer( Layer* layer );
		void PushOverlay( Layer* layer );

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

	private:
		bool OnWindowClose( WindowCloseEvent& e );

		std::unique_ptr< Window > m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
#pragma warning( pop )