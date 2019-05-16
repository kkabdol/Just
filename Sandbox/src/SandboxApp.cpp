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
		JST_INFO( "ExampleLayer::Update" );
	}

	virtual void OnEvent( Just::Event& event ) override
	{
		JST_TRACE( "{0}", event );
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