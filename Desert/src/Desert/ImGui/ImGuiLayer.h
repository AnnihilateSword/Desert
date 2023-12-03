#pragma once

#include "Desert/Layer.h"

#include "Desert/Events/ApplicationEvent.h"
#include "Desert/Events/KeyEvent.h"
#include "Desert/Events/MouseEvent.h"

struct ImGuiContext;

namespace Desert {

	class DESERT_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

		ImGuiContext* GetImGuiContext();

	private:
		float m_Time = 0.0f;
	};

}