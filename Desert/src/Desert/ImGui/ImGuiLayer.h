#pragma once

#include "Desert/Layer.h"

namespace Desert {

	class DESERT_API ImguiLayer : public Layer
	{
	public:
		ImguiLayer();
		~ImguiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		float m_Time = 0.0f;
	};

}