#pragma once

#include "Event.h"

namespace Just
{
	class JUST_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY( EventCategoryKeyboard | EventCategoryInput )

	protected:
		KeyEvent( int keycode )
			: m_KeyCode( keycode ) {}

		int m_KeyCode;
	};

	class JUST_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent( int keycode, int repeatCount )
			: KeyEvent( keycode ), m_RepeatCount( repeatCount ) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << GetKeyCode() << " (" << GetRepeatCount() << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE( KeyPressed )
	private:
		int m_RepeatCount;
	};

	class JUST_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent( int keycode, int repeatCount )
			: KeyEvent( keycode ), m_RepeatCount( repeatCount ) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << GetKeyCode() << " (" << GetRepeatCount() << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE( KeyReleased )
	private:
		int m_RepeatCount;
	};

	class JUST_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent( int keycode )
			: KeyEvent( keycode ) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << GetKeyCode();
			return ss.str();
		}

		EVENT_CLASS_TYPE( KeyTyped )
	};
}