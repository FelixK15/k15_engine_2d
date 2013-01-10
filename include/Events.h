#pragma once

#ifndef __PREDEFINEDENGINEEVENTS__
#define __PREDEFINEDENGINEEVENTS__

#include "Event.h"

namespace K15_Engine
{
	class K15ENGINE_API Events
	{

	public:

		static const EventType MouseMoved;

		static const EventType MousePressed;

		static const EventType MouseReleased;

		static const EventType KeyboardPressed;

		static const EventType KeyboardReleased;

		static const EventType UnicodeKeyboardPressed;

		static const EventType FocusGained;

		static const EventType FocusLost;

		static const EventType WindowClosed;

		static const EventType ResourceCached;

		static const EventType ResourceCreated;

		static const EventType ResourceDestroyed;

		static const EventType AnimationFinished;

		static const EventType AnimationStarted;

		static const EventType TimerStarted;

		static const EventType TimerStopped;

		static const EventType TimerPaused;

		static const EventType GameObjectCreated;

		static const EventType BeforeGameObjectUpdate;

		static const EventType AfterGameObjectUpdate;

		static const EventType BeforeDeleteGameObject;

		static const EventType GameObjectDeleted;

		static const EventType GameObjectStateChanged;

		static const EventType ObjectMoved;

		static const EventType ForcePositionBroadcast;

		static const EventType PositionBroadcast;

		static const EventType NewAlpha;

		static const EventType NewColor;

		static const EventType NewSize;

		static const EventType RestoreOriginalGraphic;

		static const EventType NewAnimation;

		static const EventType MessageLogged;

	};
}

#endif //__PREDEFINEDENGINEEVENTS__