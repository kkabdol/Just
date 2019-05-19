#pragma once

#include "Just/Input.h"

namespace Just
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool GetKeyPressedImpl( int keycode ) override;
		virtual std::pair< float, float > GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}