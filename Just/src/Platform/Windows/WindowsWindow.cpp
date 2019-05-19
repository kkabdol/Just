#include "jstpch.h"
#include "WindowsWindow.h"

#include "Just/Events/ApplicationEvent.h"
#include "Just/Events/KeyEvent.h"
#include "Just/Events/MouseEvent.h"

#include <glad/glad.h>

namespace Just
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create( const WindowProps& props )
	{
		return new WindowsWindow( props );
	}

	WindowsWindow::WindowsWindow( const WindowProps& props )
	{
		Init( props );
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers( m_Window );
	}

	void WindowsWindow::SetVSync( bool enabled )
	{
		if( enabled )
		{
			glfwSwapInterval( 1 );
		}
		else
		{
			glfwSwapInterval( 0 );
		}

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return false;
	}

	void* WindowsWindow::GetNativeWindow()
	{
		return m_Window;
	}

	void WindowsWindow::Init( const WindowProps& props )
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		JST_CORE_INFO( "Creating Window {0}, ({1}, {2})", props.Title, props.Width, props.Height );

		if( !s_GLFWInitialized )
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			JST_CORE_ASSERT( success, "Could not initialize GLFW!" );

			glfwSetErrorCallback( []( int error, const char* description )
			{
				JST_CORE_ERROR( "GLFW Error ({0}): {1}", error, description );
			});
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow( static_cast<int>( props.Width ), static_cast< int >( props.Height ), m_Data.Title.c_str(), nullptr, nullptr );
		glfwMakeContextCurrent( m_Window );
		int status = gladLoadGLLoader( ( GLADloadproc )glfwGetProcAddress );
		JST_CORE_ASSERT( status, "Failed to initialize glad!" );
		glfwSetWindowUserPointer( m_Window, &m_Data );
		SetVSync( true );

		// Set GFLW callbacks
		glfwSetWindowSizeCallback( m_Window, []( GLFWwindow* window, int width, int height )
		{
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event( width, height );
			data.EventCallback( event );
		});

		glfwSetWindowCloseCallback( m_Window, []( GLFWwindow* window )
		{
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );
			WindowCloseEvent event;
			data.EventCallback( event );
		});

		glfwSetKeyCallback( m_Window, []( GLFWwindow* window, int key, int scancode, int action, int mods )
		{
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );
			
			switch( action )
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event( key, 0 );
				data.EventCallback( event );
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event( key, 0 );
				data.EventCallback( event );
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event( key, 1 );
				data.EventCallback( event );
				break;
			}
			}
		});

		glfwSetCharCallback( m_Window, []( GLFWwindow* window, unsigned int key )
		{
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );

			KeyTypedEvent event( key );
			data.EventCallback( event );
		});

		glfwSetMouseButtonCallback( m_Window, []( GLFWwindow* window, int button, int action, int mods )
		{
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );
			
			switch ( action )
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event( button );
				data.EventCallback( event );
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event( button );
				data.EventCallback( event );
				break;
			}
			}
		});

		glfwSetScrollCallback( m_Window, []( GLFWwindow* window, double xOffset, double yOffset )
		{
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );
			
			MouseScrolledEvent event( static_cast< float >( xOffset ), static_cast< float >( yOffset ) );
			data.EventCallback( event );
		});

		glfwSetCursorPosCallback( m_Window, []( GLFWwindow* window, double xPos, double yPos )
		{
			WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );

			MouseMovedEvent event( static_cast< float >( xPos ), static_cast< float >( yPos ) );
			data.EventCallback( event );
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow( m_Window );
	}


}
