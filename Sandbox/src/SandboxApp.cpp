#include <Just.h>

class Sandbox : public Just::Application
{
public:
	Sandbox()
	{
		JST_INFO( "Created Sandbox!" );
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