#include <Desert.h>

class ExampleLayer : public Desert::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnAttach() override
	{
	}

	void OnDetach() override
	{
	}

	void OnUpdate() override
	{
		DESERT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Desert::Event& event) override
	{
		DESERT_TRACE("{0}", event);
	}

};

class Sandbox : public Desert::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Desert::Application* Desert::CreateApplication()
{
	return new Sandbox();
}