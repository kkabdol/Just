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
		static void Begin();
		static void End();

		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
	private:
		
		float m_Time = 0.0f;
	};
}