#include "DesertPCH.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include "Desert/Input.h"

namespace Desert {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	ImGuiLayer* Application::s_ImGuiLayer = nullptr;

	Application::Application()
	{
		DT_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		// 创建窗口
		m_Window = std::unique_ptr<Window>(Window::Create());
		// 设置窗口的事件回调函数
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		s_ImGuiLayer = new ImGuiLayer();
		// 在尾部插入
		PushOverlay(s_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// 从前往后渲染 Layer
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			s_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			s_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		// 从后往前遍历执行时间
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}