#pragma once

#include "Just/Core.h"

namespace Just
{
	class JUST_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}

