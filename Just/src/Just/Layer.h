#pragma once

#include "Just/Core.h"
#include "Just/Events/Event.h"

namespace Just
{
	class JUST_API Layer
	{
	public:
		Layer( const std::string& debugName = "Layer" );
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent( Event& event ) {}

		inline const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}