#include <Desert.h>

#include "imgui.h"

class ExampleLayer : public Desert::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	virtual void OnAttach() override
	{
	}

	virtual void OnDetach() override
	{
	}

	virtual void OnUpdate() override
	{
		if (Desert::Input::IsKeyPressed(DT_KEY_TAB))
		{
			DT_TRACE("Tab key is pressed!");
		}
	}

	virtual void OnEvent(Desert::Event& event) override
	{
		if (event.GetEventType() == Desert::EventType::ET_KeyPressed)
		{
			Desert::KeyReleasedEvent& e = (Desert::KeyReleasedEvent&)event;
			DT_CORE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}


	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Text");
		ImGui::Text("Hello Desert");
		ImGui::End();
	}

};

class Sandbox : public Desert::Application
{
public:
	Sandbox()
	{
		ImGui::SetCurrentContext(Application::Get().GetImGuiContext());
		// 在头部插入
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