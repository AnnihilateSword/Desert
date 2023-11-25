#pragma once

#include "DesertPCH.h"
#include "Desert/Core.h"

namespace Desert {

	// Desert �е��¼�Ŀǰ�������ģ�����ζ�ŵ��¼�����ʱ������
	// �¼����������ɷ����������ϴ���
	// ��δ�������õĲ��Կ����ǽ��¼����嵽�¼�
	// �����л����¼������ڸ��½׶ε� "�¼� "���ִ������ǡ�

	enum class EventType
	{
		None = 0,
		ET_WindowClose, ET_WindowResize, ET_WindowFocus, ET_WindowLostFocus, ET_WindowMoved,
		ET_AppTick, ET_AppUpdate, ET_AppRender,
		ET_KeyPressed, ET_KeyReleased,
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
				// eg. *(KeyEvent*)&m_Event����ȡ��ַ����ת�����ͣ��ٽ�����
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