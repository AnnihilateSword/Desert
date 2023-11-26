#pragma once

#include "DesertPCH.h"
#include "Desert/Core.h"

namespace Desert {

	// Desert 中的事件目前是阻塞的，这意味着当事件发生时，它会
	// 事件会立即被派发，必须马上处理。
	// 在未来，更好的策略可能是将事件缓冲到事件
	// 总线中缓冲事件，并在更新阶段的 "事件 "部分处理它们。

	enum class EventType
	{
		None = 0,
		ET_WindowClose, ET_WindowResize, ET_WindowFocus, ET_WindowLostFocus, ET_WindowMoved,
		ET_AppTick, ET_AppUpdate, ET_AppRender,
		ET_KeyPressed, ET_KeyReleased, ET_KeyTyped,
		ET_MouseButtonPressed, ET_MouseButtonReleased, ET_MouseMoved, ET_MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EC_Application = BIT(0),
		EC_Input       = BIT(1),
		EC_Keyboard    = BIT(2),
		EC_Mouse       = BIT(3),
		EC_MouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class DESERT_API Event
	{
		friend class EventDispatcher;
	public:
		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// eg. *(KeyEvent*)&m_Event，先取地址，再转换类型，再解引用
				m_Event.Handled = func(*(T*)&m_Event);
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}