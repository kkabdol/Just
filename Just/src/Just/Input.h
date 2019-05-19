#pragma once

#include "Just/Core.h"

namespace Just
{
	class JUST_API Input
	{
	public:
		inline static bool GetKeyPressed( int keycode ) { return s_Instance->GetKeyPressedImpl( keycode ); }
		inline static std::pair< float, float > GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

	protected:
		virtual bool GetKeyPressedImpl( int keycode ) = 0;
		virtual std::pair< float, float > GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instance;
	};
}