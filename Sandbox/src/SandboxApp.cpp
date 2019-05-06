#include <Just.h>

class Sandbox : public Just::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Just::Application* Just::CreateApplication()
{
	return new Sandbox();
}