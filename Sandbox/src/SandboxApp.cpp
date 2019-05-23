#include <Just.h>

class ExampleLayer : public Just::Layer
{
public:
	ExampleLayer()
		: Layer( "Example" )
	{
	}

	virtual void OnUpdate() override
	{
		if( Just::Input::IsKeyPressed( JST_KEY_TAB ) )
		{
			JST_TRACE( "Tab key is pressed( poll )!" );
		}
	}

	virtual void OnEvent( Just::Event& event ) override
	{
		if( event.GetEventType() == Just::EventType::KeyPressed )
		{
			Just::KeyPressedEvent& e = ( Just::KeyPressedEvent& )event;
			if ( e.GetKeyCode() == JST_KEY_TAB )
			{
				JST_TRACE( "Tab key is pressed( event )!" );
			}
			JST_TRACE( "{0}", ( char )e.GetKeyCode() );
		}
	}
};

class Sandbox : public Just::Application
{
public:
	Sandbox()
	{
		PushLayer( new ExampleLayer );
		PushOverlay( new Just::ImGuiLayer );
	}

	~Sandbox()
	{

	}

	void Run()
	{
	}
};

Just::Application* Just::CreateApplication()
{
	return new Sandbox();
}