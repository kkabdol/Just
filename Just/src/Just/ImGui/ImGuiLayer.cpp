#include "jstpch.h"
#include "ImGuiLayer.h"

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

#include "Just/Application.h"

namespace Just
{
	ImGuiLayer::ImGuiLayer()
		: Layer( "ImGuiLayer" )
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();

		// Enable Gamepad Navigation
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Just key codes
		io.KeyMap[ ImGuiKey_Tab ] = GLFW_KEY_TAB;
		io.KeyMap[ ImGuiKey_LeftArrow ] = GLFW_KEY_LEFT;
		io.KeyMap[ ImGuiKey_RightArrow ] = GLFW_KEY_RIGHT;
		io.KeyMap[ ImGuiKey_UpArrow ] = GLFW_KEY_UP;
		io.KeyMap[ ImGuiKey_DownArrow ] = GLFW_KEY_DOWN;
		io.KeyMap[ ImGuiKey_PageUp ] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ ImGuiKey_PageDown ] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ ImGuiKey_Home ] = GLFW_KEY_HOME;
		io.KeyMap[ ImGuiKey_End ] = GLFW_KEY_END;
		io.KeyMap[ ImGuiKey_Insert ] = GLFW_KEY_INSERT;
		io.KeyMap[ ImGuiKey_Delete ] = GLFW_KEY_DELETE;
		io.KeyMap[ ImGuiKey_Backspace ] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ ImGuiKey_Space ] = GLFW_KEY_SPACE;
		io.KeyMap[ ImGuiKey_Enter ] = GLFW_KEY_ENTER;
		io.KeyMap[ ImGuiKey_Escape ] = GLFW_KEY_ESCAPE;
		io.KeyMap[ ImGuiKey_A ] = GLFW_KEY_A;
		io.KeyMap[ ImGuiKey_C ] = GLFW_KEY_C;
		io.KeyMap[ ImGuiKey_V ] = GLFW_KEY_V;
		io.KeyMap[ ImGuiKey_X ] = GLFW_KEY_X;
		io.KeyMap[ ImGuiKey_Y ] = GLFW_KEY_Y;
		io.KeyMap[ ImGuiKey_Z ] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init( "#version 410" );
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		UpdateGamepads();

		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2( static_cast< float >( app.GetWindow().GetWidth() ), static_cast< float >( app.GetWindow().GetHeight() ) );

		float time = ( float )glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? ( time - m_Time ) : ( 1.0f / 60.0f );
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow( &show );

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
	}

	void ImGuiLayer::OnEvent( Event & event )
	{
		EventDispatcher dispatcher( event );
		dispatcher.Dispatch< KeyPressedEvent >( JST_BIND_EVENT_FN( ImGuiLayer::OnKeyPressed ) );
		dispatcher.Dispatch< KeyReleasedEvent >( JST_BIND_EVENT_FN( ImGuiLayer::OnKeyReleased ) );
		dispatcher.Dispatch< KeyTypedEvent >( JST_BIND_EVENT_FN( ImGuiLayer::OnKeyTyped ) );
		dispatcher.Dispatch< MouseButtonPressedEvent >( JST_BIND_EVENT_FN( ImGuiLayer::OnMouseButtonPressed ) );
		dispatcher.Dispatch< MouseButtonReleasedEvent >( JST_BIND_EVENT_FN( ImGuiLayer::OnMouseButtonReleased ) );
		dispatcher.Dispatch< MouseMovedEvent >( JST_BIND_EVENT_FN( ImGuiLayer::OnMouseMoved ) );
		dispatcher.Dispatch< MouseScrolledEvent >( JST_BIND_EVENT_FN( ImGuiLayer::OnMouseScrolled ) );
		dispatcher.Dispatch< WindowResizeEvent >( JST_BIND_EVENT_FN( ImGuiLayer::OnWindowResized ) );
	}

	void ImGuiLayer::UpdateGamepads()
	{
		ImGuiIO& io = ImGui::GetIO();
		memset(io.NavInputs, 0, sizeof(io.NavInputs));
		if ((io.ConfigFlags & ImGuiConfigFlags_NavEnableGamepad) == 0)
			return;

		// Update gamepad inputs
		#define MAP_BUTTON(NAV_NO, BUTTON_NO)       { if (buttons_count > BUTTON_NO && buttons[BUTTON_NO] == GLFW_PRESS) io.NavInputs[NAV_NO] = 1.0f; }
		#define MAP_ANALOG(NAV_NO, AXIS_NO, V0, V1) { float v = (axes_count > AXIS_NO) ? axes[AXIS_NO] : V0; v = (v - V0) / (V1 - V0); if (v > 1.0f) v = 1.0f; if (io.NavInputs[NAV_NO] < v) io.NavInputs[NAV_NO] = v; }
		int axes_count = 0, buttons_count = 0;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axes_count);
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttons_count);
		MAP_BUTTON(ImGuiNavInput_Activate,   0);     // Cross / A
		MAP_BUTTON(ImGuiNavInput_Cancel,     1);     // Circle / B
		MAP_BUTTON(ImGuiNavInput_Menu,       2);     // Square / X
		MAP_BUTTON(ImGuiNavInput_Input,      3);     // Triangle / Y
		MAP_BUTTON(ImGuiNavInput_DpadLeft,   13);    // D-Pad Left
		MAP_BUTTON(ImGuiNavInput_DpadRight,  11);    // D-Pad Right
		MAP_BUTTON(ImGuiNavInput_DpadUp,     10);    // D-Pad Up
		MAP_BUTTON(ImGuiNavInput_DpadDown,   12);    // D-Pad Down
		MAP_BUTTON(ImGuiNavInput_FocusPrev,  4);     // L1 / LB
		MAP_BUTTON(ImGuiNavInput_FocusNext,  5);     // R1 / RB
		MAP_BUTTON(ImGuiNavInput_TweakSlow,  4);     // L1 / LB
		MAP_BUTTON(ImGuiNavInput_TweakFast,  5);     // R1 / RB
		MAP_ANALOG(ImGuiNavInput_LStickLeft, 0,  -0.3f,  -0.9f);
		MAP_ANALOG(ImGuiNavInput_LStickRight,0,  +0.3f,  +0.9f);
		MAP_ANALOG(ImGuiNavInput_LStickUp,   1,  +0.3f,  +0.9f);
		MAP_ANALOG(ImGuiNavInput_LStickDown, 1,  -0.3f,  -0.9f);
		#undef MAP_BUTTON
		#undef MAP_ANALOG
		if (axes_count > 0 && buttons_count > 0)
			io.BackendFlags |= ImGuiBackendFlags_HasGamepad;
		else
			io.BackendFlags &= ~ImGuiBackendFlags_HasGamepad;
	}

	bool ImGuiLayer::OnKeyPressed( KeyPressedEvent & e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[ e.GetKeyCode() ] = true;

		io.KeyCtrl = io.KeysDown[ GLFW_KEY_LEFT_CONTROL ] || io.KeysDown[ GLFW_KEY_RIGHT_CONTROL ];
		io.KeyShift = io.KeysDown[ GLFW_KEY_LEFT_SHIFT ] || io.KeysDown[ GLFW_KEY_RIGHT_SHIFT ];
		io.KeyAlt = io.KeysDown[ GLFW_KEY_LEFT_ALT ] || io.KeysDown[ GLFW_KEY_RIGHT_ALT ];
		io.KeySuper = io.KeysDown[ GLFW_KEY_LEFT_SUPER ] || io.KeysDown[ GLFW_KEY_RIGHT_SUPER ];

		return false;
	}

	bool ImGuiLayer::OnKeyReleased( KeyReleasedEvent & e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[ e.GetKeyCode() ] = false;

		io.KeyCtrl = io.KeysDown[ GLFW_KEY_LEFT_CONTROL ] || io.KeysDown[ GLFW_KEY_RIGHT_CONTROL ];
		io.KeyShift = io.KeysDown[ GLFW_KEY_LEFT_SHIFT ] || io.KeysDown[ GLFW_KEY_RIGHT_SHIFT ];
		io.KeyAlt = io.KeysDown[ GLFW_KEY_LEFT_ALT ] || io.KeysDown[ GLFW_KEY_RIGHT_ALT ];
		io.KeySuper = io.KeysDown[ GLFW_KEY_LEFT_SUPER ] || io.KeysDown[ GLFW_KEY_RIGHT_SUPER ];

		return false;
	}

	bool ImGuiLayer::OnKeyTyped( KeyTypedEvent & e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter( static_cast< unsigned int >( e.GetKeyCode() ) );

		return false;
	}

	bool ImGuiLayer::OnMouseButtonPressed( MouseButtonPressedEvent & e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[ e.GetMouseButton() ] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleased( MouseButtonReleasedEvent & e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[ e.GetMouseButton() ] = false;
		
		return false;
	}

	bool ImGuiLayer::OnMouseMoved( MouseMovedEvent & e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2( e.GetX(), e.GetY() );
		
		return false;
	}

	bool ImGuiLayer::OnMouseScrolled( MouseScrolledEvent & e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel = e.GetYOffset();
		io.MouseWheelH = e.GetXOffset();
		
		return false;
	}

	bool ImGuiLayer::OnWindowResized( WindowResizeEvent & e )
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2( static_cast< float >( e.GetWidth() ), static_cast< float >( e.GetHeight() ) );
		io.DisplayFramebufferScale = ImVec2( 1.0f, 1.0f );
		glViewport( 0, 0, e.GetWidth(), e.GetHeight() );	// TODO: I don't think this should be here.

		return false;
	}
}