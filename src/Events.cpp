#include "Events.h"

using namespace K15_Engine;

const EventType Events::MouseMoved = EventType("mouse_moved");

const EventType Events::MousePressed = EventType("mouse_pressed");

const EventType Events::MouseReleased = EventType("mouse_released");

const EventType Events::KeyboardPressed = EventType("keyboard_pressed");

const EventType Events::KeyboardReleased = EventType("keyboard_released");

const EventType Events::UnicodeKeyboardPressed = EventType("Unicode_Keyboard_pressed");

const EventType Events::FocusGained = EventType("focus_gained");

const EventType Events::FocusLost = EventType("focus_lost");

const EventType Events::WindowClosed = EventType("window_closed");

const EventType Events::ResourceCached = EventType("resource_cached");

const EventType Events::ResourceCreated = EventType("resource_created");

const EventType Events::ResourceDestroyed = EventType("resource_destroyed");

const EventType Events::AnimationFinished = EventType("animation_finished");

const EventType Events::AnimationStarted = EventType("animation_started");

const EventType Events::TimerStarted = EventType("timer_started");

const EventType Events::TimerStopped = EventType("timer_stopped");

const EventType Events::TimerPaused = EventType("timer_paused");

const EventType Events::GameObjectCreated = EventType("gameobject_created");

const EventType Events::BeforeGameObjectUpdate = EventType("before_gameobject_update");

const EventType Events::AfterGameObjectUpdate = EventType("after_gameobject_update");

const EventType Events::BeforeDeleteGameObject = EventType("before_gameobject_deletion");

const EventType Events::GameObjectDeleted = EventType("gameobject_deleted");

const EventType Events::GameObjectStateChanged = EventType("gameobject_state_changed");

const EventType Events::ObjectMoved = EventType("object_moved");

const EventType Events::ForcePositionBroadcast = EventType("force_position_broadcast");

const EventType Events::PositionBroadcast = EventType("position_broadcast");

const EventType Events::NewAlpha = EventType("new_alpha");

const EventType Events::NewColor = EventType("new_color");

const EventType Events::NewSize = EventType("new_size");

const EventType Events::RestoreOriginalGraphic = EventType("restore_original_graphic");

const EventType Events::NewAnimation = EventType("new_animation");

const EventType Events::MessageLogged = EventType("message_logged");