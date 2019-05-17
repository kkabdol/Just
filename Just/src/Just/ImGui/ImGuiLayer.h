#pragma once

#include "Just/Layer.h"
#include "Just/Events/KeyEvent.h"
#include "Just/Events/MouseEvent.h"
#include "Just/Events/ApplicationEvent.h"

namespace Just
{
	class JUST_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnUpdate() override;
		virtual void OnEvent( Event& event ) override;
	private:
		void UpdateGamepads();

		bool OnKeyPressed( KeyPressedEvent& e );
		bool OnKeyReleased( KeyReleasedEvent& e );
		bool OnKeyTyped( KeyTypedEvent& e );
		bool OnMouseButtonPressed( MouseButtonPressedEvent& e );
		bool OnMouseButtonReleased( MouseButtonReleasedEvent& e );
		bool OnMouseMoved( MouseMovedEvent& e );
		bool OnMouseScrolled( MouseScrolledEvent& e );
		bool OnWindowResized( WindowResizeEvent& e );

		float m_Time = 0.0f;
	};
}