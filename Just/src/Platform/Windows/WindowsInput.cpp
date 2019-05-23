#include "jstpch.h"
#include "WindowsInput.h"

#include "Just/Application.h"
#include <GLFW/glfw3.h>

namespace Just
{
	Input* Input::s_Instance = new WindowsInput();

	bool Just::WindowsInput::IsKeyPressedImpl( int keycode )
	{
		auto window = static_cast< GLFWwindow* >( Application::Get().GetWindow().GetNativeWindow() );
		auto state = glfwGetKey( window, keycode );
		return state == GLFW_PRESS;
	}

	bool WindowsInput::IsMouseButtonPressedImpl( int button )
	{
		auto window = static_cast< GLFWwindow* >( Application::Get().GetWindow().GetNativeWindow() );
		auto state = glfwGetMouseButton( window, button );
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast< GLFWwindow* >( Application::Get().GetWindow().GetNativeWindow() );
		double xpos, ypos;
		glfwGetCursorPos( window, &xpos, &ypos );

		return { static_cast< float >( xpos ), static_cast< float >( ypos ) };
	}

	float WindowsInput::GetMouseXImpl()
	{
	#if ( __cplusplus >= 201703L )
		auto[ x, y ] = GetMousePositionImpl();
		return x;
	#else
	#pragma message ( JST_WARNING "C++17 is preferable." )
		auto v = GetMousePositionImpl();
		return std::get<0>( v );
	#endif
	}

	float WindowsInput::GetMouseYImpl()
	{
	#if ( __cplusplus >= 201703L )
		auto[ x, y ] = GetMousePositionImpl();
		return y;
	#else
	#pragma message ( JST_WARNING "C++17 is preferable." )
		auto v = GetMousePositionImpl();
		return std::get<1>( v );
	#endif
	}
}
