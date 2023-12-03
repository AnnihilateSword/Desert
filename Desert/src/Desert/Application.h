#pragma once

#include "Core.h"

#include "Window.h"
#include "Desert/LayerStack.h"
#include "Desert/Events/Event.h"
#include "Desert/Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

namespace Desert {

	class DESERT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() const { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
		inline static ImGuiContext* GetImGuiContext() { return s_ImGuiLayer->GetImGuiContext(); }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
		static ImGuiLayer* s_ImGuiLayer;
	};

	// 在客户端定义
	Application* CreateApplication();
}