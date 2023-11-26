#include "DesertPCH.h"
#include "WindowsInput.h"

#include "Desert/Application.h"
#include <GLFW/glfw3.h>

namespace Desert {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { xpos, ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto p = GetMousePositionImpl();
		return std::get<0>(p);
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto p = GetMousePositionImpl();
		return std::get<1>(p);
	}

}