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
		if (Desert::Input::IsKeyPressed(DT_KEY_TAB))
		{
			DT_TRACE("Tab key is pressed!");
		}
	}

	void OnEvent(Desert::Event& event) override
	{
		if (event.GetEventType() == Desert::EventType::ET_KeyPressed)
		{
			Desert::KeyReleasedEvent& e = (Desert::KeyReleasedEvent&)event;
			DT_CORE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Desert::Application
{
public:
	Sandbox()
	{
		// 在头部插入
		PushLayer(new ExampleLayer());
		// 在尾部插入
		PushOverlay(new Desert::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Desert::Application* Desert::CreateApplication()
{
	return new Sandbox();
}