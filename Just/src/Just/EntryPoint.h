#pragma once

#ifdef JST_PLATFORM_WINDOWS

extern Just::Application* Just::CreateApplication();

int main( int argc, char** argv )
{
	auto app = Just::CreateApplication();
	app->Run();
	delete app;

	return 0;
}

#endif