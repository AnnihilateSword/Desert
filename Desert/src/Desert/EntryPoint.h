#pragma once

#ifdef DESERT_PLATFORM_WINDOWS

extern Desert::Application* Desert::CreateApplication();

int main(int argc, char** argv)
{
	Desert::Log::Init();
	DT_CORE_WARN("Initialized Log!");
	int a = 5;
	DT_ERROR("Hello! var={0}", a);

	auto app = Desert::CreateApplication();
	app->Run();
	delete app;
}

#endif