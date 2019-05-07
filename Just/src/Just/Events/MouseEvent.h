#pragma once

#include "Event.h"

#include <sstream>

namespace Just
{
	class JUST_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent( float x, float y )
			: m_MouseX( x ), m_MouseY( y ) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << GetX() << ", " << GetY();
			return ss.str();
		}

		EVENT_CLASS_TYPE( MouseMoved )
		EVENT_CLASS_CATEGORY( EventCategoryMouse | EventCategoryInput )

	private:
		float m_MouseX, m_MouseY;
	};

	class JUST_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent( float xOffset, float yOffset )
			: m_XOffset( xOffset ), m_YOffset( yOffset ) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE( MouseMoved )
		EVENT_CLASS_CATEGORY( EventCategoryMouse | EventCategoryInput )

	private:
		float m_XOffset, m_YOffset;
	};

	class JUST_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY( EventCategoryMouse | EventCategoryInput )

	protected:
		MouseButtonEvent( int button )
			: m_Button( button ) {}

		int m_Button;
	};

	class JUST_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent( int button )
			: MouseButtonEvent( button ) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << GetMouseButton();
			return ss.str();
		}

		EVENT_CLASS_TYPE( MouseButtonPressed )
	};

	class JUST_API MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent( int button )
			: MouseButtonEvent( button ) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleaseEvent: " << GetMouseButton();
			return ss.str();
		}

		EVENT_CLASS_TYPE( MouseButtonReleased )
	};
}