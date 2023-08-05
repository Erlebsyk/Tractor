// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// Standard library includes
#include <functional>

namespace test
{
	struct ApplicationEventTests
	{
		static uint32_t window_close_n;
		static uint32_t window_focus_n;
		static uint32_t window_lost_focus_n;
		static uint32_t window_width;
		static uint32_t window_height;
		static uint32_t window_pos_x;
		static uint32_t window_pos_y;
		static uint32_t ticks_n;
		static uint32_t updates_n;
		static uint32_t renders_n;

		static void reset()
		{
			window_close_n = 0;
			window_focus_n = 0;
			window_lost_focus_n = 0;
			window_width = 0;
			window_height = 0;
			window_pos_x = 0;
			window_pos_y = 0;
			ticks_n = 0;
			updates_n = 0;
			renders_n = 0;
		}

		static void window_close_cb_b(trac::Event& e) { window_close_n++; }
		static void window_close_cb_nb(std::shared_ptr<trac::Event>& e) { window_close_n++; }

		static void window_focus_cb_b(trac::Event& e) { window_focus_n++; }
		static void window_focus_cb_nb(std::shared_ptr<trac::Event>& e) { window_focus_n++; }

		static void window_lost_focus_cb_b(trac::Event& e) { window_lost_focus_n++; }
		static void window_lost_focus_cb_nb(std::shared_ptr<trac::Event>& e) { window_lost_focus_n++; }


		static void tick_cb_b(trac::Event& e) { ticks_n++; }
		static void tick_cb_nb(std::shared_ptr<trac::Event>& e) { ticks_n++; }

		static void update_cb_b(trac::Event& e) { updates_n++; }
		static void update_cb_nb(std::shared_ptr<trac::Event>& e) { updates_n++; }

		static void render_cb_b(trac::Event& e) { renders_n++; }
		static void render_cb_nb(std::shared_ptr<trac::Event>& e) { renders_n++; }
		
		static void window_resize_cb_b(trac::Event& e)
		{
			trac::EventWindowResize& e_resize = static_cast<trac::EventWindowResize&>(e);
			window_width = e_resize.GetWidth();
			window_height = e_resize.GetHeight();
		}
		static void window_resize_cb_nb(std::shared_ptr<trac::Event>& e)
		{
			std::shared_ptr<trac::EventWindowResize> e_resize = std::static_pointer_cast<trac::EventWindowResize>(e);
			window_width = e_resize->GetWidth();
			window_height = e_resize->GetHeight();
		}

		static void window_moved_cb_b(trac::Event& e)
		{
			trac::EventWindowMoved& e_move = static_cast<trac::EventWindowMoved&>(e);
			window_pos_x = e_move.GetX();
			window_pos_y = e_move.GetY();
		}
		static void window_moved_cb_nb(std::shared_ptr<trac::Event>& e)
		{
			std::shared_ptr<trac::EventWindowMoved> e_move = std::static_pointer_cast<trac::EventWindowMoved>(e);
			window_pos_x = e_move->GetX();
			window_pos_y = e_move->GetY();
		}
	};
	uint32_t ApplicationEventTests::window_close_n = 0;
	uint32_t ApplicationEventTests::window_focus_n = 0;
	uint32_t ApplicationEventTests::window_lost_focus_n = 0;
	uint32_t ApplicationEventTests::window_width = 0;
	uint32_t ApplicationEventTests::window_height = 0;
	uint32_t ApplicationEventTests::window_pos_x = 0;
	uint32_t ApplicationEventTests::window_pos_y = 0;
	uint32_t ApplicationEventTests::ticks_n = 0;
	uint32_t ApplicationEventTests::updates_n = 0;
	uint32_t ApplicationEventTests::renders_n = 0;

	struct KeyEventTests
	{
		static uint32_t presses_n;
		static uint32_t releases_n;
		static uint32_t typed_n;
		static trac::KeyCode last_key;

		static void reset()
		{
			presses_n = 0;
			releases_n = 0;
			typed_n = 0;
			last_key = trac::KeyCode::SDLK_UNKNOWN;
		}

		static void press_cb_b(trac::Event& e)
		{
			trac::EventKeyPressed& e_press = static_cast<trac::EventKeyPressed&>(e);
			last_key = e_press.GetKeyCode();
			presses_n++;
		}
		static void press_cb_nb(std::shared_ptr<trac::Event>& e)
		{
			std::shared_ptr<trac::EventKeyPressed> e_press = std::static_pointer_cast<trac::EventKeyPressed>(e);
			last_key = e_press->GetKeyCode();
			presses_n++;
		}

		static void release_cb_b(trac::Event& e)
		{
			trac::EventKeyReleased& e_release = static_cast<trac::EventKeyReleased&>(e);
			last_key = e_release.GetKeyCode();
			releases_n++;
		}
		static void release_cb_nb(std::shared_ptr<trac::Event>& e)
		{
			std::shared_ptr<trac::EventKeyReleased> e_release = std::static_pointer_cast<trac::EventKeyReleased>(e);
			last_key = e_release->GetKeyCode();
			releases_n++;
		}

		static void typed_cb_b(trac::Event& e)
		{
			trac::EventKeyTyped& e_typed = static_cast<trac::EventKeyTyped&>(e);
			last_key = e_typed.GetKeyCode();
			typed_n++;
		}
		static void typed_cb_nb(std::shared_ptr<trac::Event>& e)
		{
			std::shared_ptr<trac::EventKeyTyped> e_typed = std::static_pointer_cast<trac::EventKeyTyped>(e);
			last_key = e_typed->GetKeyCode();
			typed_n++;
		}
	};
	uint32_t KeyEventTests::presses_n = 0;
	uint32_t KeyEventTests::releases_n = 0;
	uint32_t KeyEventTests::typed_n = 0;
	trac::KeyCode KeyEventTests::last_key = trac::KeyCode::SDLK_UNKNOWN;

	struct MouseEventTests
	{
		static uint32_t presses_n;
		static uint32_t releases_n;
		static trac::MouseCode last_button;
		static float pos_x;
		static float pos_y;
		static float scroll_x;
		static float scroll_y;

		static void reset()
		{
			presses_n = 0;
			releases_n = 0;
			last_button = trac::MouseCode::kUnknown;
			pos_x = 0.0f;
			pos_y = 0.0f;
			scroll_x = 0.0f;
			scroll_y = 0.0f;
		}

		static void press_cb_b(trac::Event& e)
		{
			trac::EventMouseButtonPress& e_mouse_press = static_cast<trac::EventMouseButtonPress&>(e);
			last_button = e_mouse_press.GetButton();
			presses_n++;
		}
		static void press_cb_nb(std::shared_ptr<trac::Event>& e)
		{
			std::shared_ptr<trac::EventMouseButtonPress> e_mouse_press = std::static_pointer_cast<trac::EventMouseButtonPress>(e);
			last_button = e_mouse_press->GetButton();
			presses_n++;
		}

		static void release_cb_b(trac::Event& e)
		{
			trac::EventMouseButtonRelease& e_mouse_release = static_cast<trac::EventMouseButtonRelease&>(e);
			last_button = e_mouse_release.GetButton();
			releases_n++;
		}
		static void release_cb_nb(std::shared_ptr<trac::Event>& e)
		{
			std::shared_ptr<trac::EventMouseButtonRelease> e_mouse_release = std::static_pointer_cast<trac::EventMouseButtonRelease>(e);
			last_button = e_mouse_release->GetButton();
			releases_n++;
		}

		static void move_cb_b(trac::Event& e)
		{
			trac::EventMouseMovement& e_mouse_move = static_cast<trac::EventMouseMovement&>(e);
			pos_x = e_mouse_move.GetX();
			pos_y = e_mouse_move.GetY();
		}
		static void move_cb_nb(std::shared_ptr<trac::Event>& e)
		{
			std::shared_ptr<trac::EventMouseMovement> e_mouse_move = std::static_pointer_cast<trac::EventMouseMovement>(e);
			pos_x = e_mouse_move->GetX();
			pos_y = e_mouse_move->GetY();
		}

		static void scroll_cb_b(trac::Event& e)
		{
			trac::EventMouseScrolled& e_mouse_scroll = static_cast<trac::EventMouseScrolled&>(e);
			scroll_x = e_mouse_scroll.GetOffsetX();
			scroll_y = e_mouse_scroll.GetOffsetY();
		}
		static void scroll_cb_nb(std::shared_ptr<trac::Event>& e)
		{
			std::shared_ptr<trac::EventMouseScrolled> e_mouse_scroll = std::static_pointer_cast<trac::EventMouseScrolled>(e);
			scroll_x = e_mouse_scroll->GetOffsetX();
			scroll_y = e_mouse_scroll->GetOffsetY();
		}
	};
	uint32_t MouseEventTests::presses_n = 0;
	uint32_t MouseEventTests::releases_n = 0;
	trac::MouseCode MouseEventTests::last_button = trac::MouseCode::kUnknown;
	float MouseEventTests::pos_x = 0.0f;
	float MouseEventTests::pos_y = 0.0f;
	float MouseEventTests::scroll_x = 0.0f;
	float MouseEventTests::scroll_y = 0.0f;

	GTEST_TEST(tractor, events_application_blocking)
	{
		trac::initialize_engine();
		KeyEventTests::reset();

		trac::EventWindowClose e_window_close;
		trac::EventWindowFocus e_window_focus;
		trac::EventWindowLostFocus e_window_lost_focus;
		trac::EventWindowResize e_window_resize(1920, 1080);
		trac::EventWindowMoved e_window_moved(10, 20);
		trac::EventAppTick e_app_tick;
		trac::EventAppUpdate e_app_update;
		trac::EventAppRender e_app_render;

		// Dispatching events should do nothing without listeners
		trac::event_dispatch_b(e_window_close);
		EXPECT_EQ(0, ApplicationEventTests::window_close_n);

		trac::event_dispatch_b(e_window_focus);
		EXPECT_EQ(0, ApplicationEventTests::window_focus_n);

		trac::event_dispatch_b(e_window_lost_focus);
		EXPECT_EQ(0, ApplicationEventTests::window_lost_focus_n);

		trac::event_dispatch_b(e_window_resize);
		EXPECT_EQ(0, ApplicationEventTests::window_width);
		EXPECT_EQ(0, ApplicationEventTests::window_height);

		trac::event_dispatch_b(e_window_moved);
		EXPECT_EQ(0, ApplicationEventTests::window_pos_x);
		EXPECT_EQ(0, ApplicationEventTests::window_pos_y);

		trac::event_dispatch_b(e_app_tick);
		EXPECT_EQ(0, ApplicationEventTests::ticks_n);

		trac::event_dispatch_b(e_app_update);
		EXPECT_EQ(0, ApplicationEventTests::updates_n);

		trac::event_dispatch_b(e_app_render);
		EXPECT_EQ(0, ApplicationEventTests::renders_n);

		// Add listeners and dispatch events
		trac::event_add_listener_b(trac::EventType::kWindowClose, ApplicationEventTests::window_close_cb_b);
		trac::event_add_listener_b(trac::EventType::kWindowFocus, ApplicationEventTests::window_focus_cb_b);
		trac::event_add_listener_b(trac::EventType::kWindowLostFocus, ApplicationEventTests::window_lost_focus_cb_b);
		trac::event_add_listener_b(trac::EventType::kWindowResize, ApplicationEventTests::window_resize_cb_b);
		trac::event_add_listener_b(trac::EventType::kWindowMoved, ApplicationEventTests::window_moved_cb_b);
		trac::event_add_listener_b(trac::EventType::kAppTick, ApplicationEventTests::tick_cb_b);
		trac::event_add_listener_b(trac::EventType::kAppUpdate, ApplicationEventTests::update_cb_b);
		trac::event_add_listener_b(trac::EventType::kAppRender, ApplicationEventTests::render_cb_b);

		trac::event_dispatch_b(e_window_close);
		EXPECT_EQ(1, ApplicationEventTests::window_close_n);

		trac::event_dispatch_b(e_window_focus);
		EXPECT_EQ(1, ApplicationEventTests::window_focus_n);

		trac::event_dispatch_b(e_window_lost_focus);
		EXPECT_EQ(1, ApplicationEventTests::window_lost_focus_n);

		trac::event_dispatch_b(e_window_resize);
		EXPECT_EQ(1920, ApplicationEventTests::window_width);
		EXPECT_EQ(1080, ApplicationEventTests::window_height);

		trac::event_dispatch_b(e_window_moved);
		EXPECT_EQ(10, ApplicationEventTests::window_pos_x);
		EXPECT_EQ(20, ApplicationEventTests::window_pos_y);

		trac::event_dispatch_b(e_app_tick);
		EXPECT_EQ(1, ApplicationEventTests::ticks_n);

		trac::event_dispatch_b(e_app_update);
		EXPECT_EQ(1, ApplicationEventTests::updates_n);

		trac::event_dispatch_b(e_app_render);
		EXPECT_EQ(1, ApplicationEventTests::renders_n);
	}

	GTEST_TEST(tractor, events_application_non_blocking)
	{
		trac::initialize_engine();
		ApplicationEventTests::reset();

		std::shared_ptr<trac::Event> e_window_close = std::make_shared<trac::EventWindowClose>();
		std::shared_ptr<trac::Event> e_window_focus = std::make_shared<trac::EventWindowFocus>();
		std::shared_ptr<trac::Event> e_window_lost_focus = std::make_shared<trac::EventWindowLostFocus>();
		std::shared_ptr<trac::Event> e_window_resize = std::make_shared<trac::EventWindowResize>(1920, 1080);
		std::shared_ptr<trac::Event> e_window_moved = std::make_shared<trac::EventWindowMoved>(10, 20);
		std::shared_ptr<trac::Event> e_app_tick = std::make_shared<trac::EventAppTick>();
		std::shared_ptr<trac::Event> e_app_update = std::make_shared<trac::EventAppUpdate>();
		std::shared_ptr<trac::Event> e_app_render = std::make_shared<trac::EventAppRender>();

		// Dispatching events should do nothing without listeners
		trac::event_dispatch_nb(e_window_close);
		EXPECT_EQ(0, ApplicationEventTests::window_close_n);

		trac::event_dispatch_nb(e_window_focus);
		EXPECT_EQ(0, ApplicationEventTests::window_focus_n);

		trac::event_dispatch_nb(e_window_lost_focus);
		EXPECT_EQ(0, ApplicationEventTests::window_lost_focus_n);

		trac::event_dispatch_nb(e_window_resize);
		EXPECT_EQ(0, ApplicationEventTests::window_width);
		EXPECT_EQ(0, ApplicationEventTests::window_height);

		trac::event_dispatch_nb(e_window_moved);
		EXPECT_EQ(0, ApplicationEventTests::window_pos_x);
		EXPECT_EQ(0, ApplicationEventTests::window_pos_y);

		trac::event_dispatch_nb(e_app_tick);
		EXPECT_EQ(0, ApplicationEventTests::ticks_n);

		trac::event_dispatch_nb(e_app_update);
		EXPECT_EQ(0, ApplicationEventTests::updates_n);

		trac::event_dispatch_nb(e_app_render);
		EXPECT_EQ(0, ApplicationEventTests::renders_n);

		trac::event_queue_process();
		EXPECT_EQ(0, ApplicationEventTests::window_close_n);
		EXPECT_EQ(0, ApplicationEventTests::window_focus_n);
		EXPECT_EQ(0, ApplicationEventTests::window_lost_focus_n);
		EXPECT_EQ(0, ApplicationEventTests::window_width);
		EXPECT_EQ(0, ApplicationEventTests::window_height);
		EXPECT_EQ(0, ApplicationEventTests::window_pos_x);
		EXPECT_EQ(0, ApplicationEventTests::window_pos_y);
		EXPECT_EQ(0, ApplicationEventTests::ticks_n);
		EXPECT_EQ(0, ApplicationEventTests::updates_n);
		EXPECT_EQ(0, ApplicationEventTests::renders_n);

		// Add listeners and dispatch events
		trac::event_add_listener_nb(trac::EventType::kWindowClose, ApplicationEventTests::window_close_cb_nb);
		trac::event_add_listener_nb(trac::EventType::kWindowFocus, ApplicationEventTests::window_focus_cb_nb);
		trac::event_add_listener_nb(trac::EventType::kWindowLostFocus, ApplicationEventTests::window_lost_focus_cb_nb);
		trac::event_add_listener_nb(trac::EventType::kWindowResize, ApplicationEventTests::window_resize_cb_nb);
		trac::event_add_listener_nb(trac::EventType::kWindowMoved, ApplicationEventTests::window_moved_cb_nb);
		trac::event_add_listener_nb(trac::EventType::kAppTick, ApplicationEventTests::tick_cb_nb);
		trac::event_add_listener_nb(trac::EventType::kAppUpdate, ApplicationEventTests::update_cb_nb);
		trac::event_add_listener_nb(trac::EventType::kAppRender, ApplicationEventTests::render_cb_nb);

		trac::event_dispatch_nb(e_window_close);
		EXPECT_EQ(0, ApplicationEventTests::window_close_n);

		trac::event_dispatch_nb(e_window_focus);
		EXPECT_EQ(0, ApplicationEventTests::window_focus_n);

		trac::event_dispatch_nb(e_window_lost_focus);
		EXPECT_EQ(0, ApplicationEventTests::window_lost_focus_n);

		trac::event_dispatch_nb(e_window_resize);
		EXPECT_EQ(0, ApplicationEventTests::window_width);
		EXPECT_EQ(0, ApplicationEventTests::window_height);

		trac::event_dispatch_nb(e_window_moved);
		EXPECT_EQ(0, ApplicationEventTests::window_pos_x);
		EXPECT_EQ(0, ApplicationEventTests::window_pos_y);

		trac::event_dispatch_nb(e_app_tick);
		EXPECT_EQ(0, ApplicationEventTests::ticks_n);

		trac::event_dispatch_nb(e_app_update);
		EXPECT_EQ(0, ApplicationEventTests::updates_n);

		trac::event_dispatch_nb(e_app_render);
		EXPECT_EQ(0, ApplicationEventTests::renders_n);

		trac::event_queue_process();
		EXPECT_EQ(1, ApplicationEventTests::window_close_n);
		EXPECT_EQ(1, ApplicationEventTests::window_focus_n);
		EXPECT_EQ(1, ApplicationEventTests::window_lost_focus_n);
		EXPECT_EQ(1920, ApplicationEventTests::window_width);
		EXPECT_EQ(1080, ApplicationEventTests::window_height);
		EXPECT_EQ(10, ApplicationEventTests::window_pos_x);
		EXPECT_EQ(20, ApplicationEventTests::window_pos_y);
		EXPECT_EQ(1, ApplicationEventTests::ticks_n);
		EXPECT_EQ(1, ApplicationEventTests::updates_n);
		EXPECT_EQ(1, ApplicationEventTests::renders_n);
	}

#if 0
	GTEST_TEST(tractor, events_application_generic)
	{
		trac::initialize_engine();
		ApplicationEventTests::reset();

		std::shared_ptr<trac::Event> e_window_close = std::make_shared<trac::EventWindowClose>();
		std::shared_ptr<trac::Event> e_window_focus = std::make_shared<trac::EventWindowFocus>();
		std::shared_ptr<trac::Event> e_window_lost_focus = std::make_shared<trac::EventWindowLostFocus>();
		std::shared_ptr<trac::Event> e_window_resize = std::make_shared<trac::EventWindowResize>(1920, 1080);
		std::shared_ptr<trac::Event> e_window_moved = std::make_shared<trac::EventWindowMoved>(10, 20);
		std::shared_ptr<trac::Event> e_app_tick = std::make_shared<trac::EventAppTick>();
		std::shared_ptr<trac::Event> e_app_update = std::make_shared<trac::EventAppUpdate>();
		std::shared_ptr<trac::Event> e_app_render = std::make_shared<trac::EventAppRender>();

		// Dispatching events should do nothing without listeners
		trac::event_dispatch(e_window_close);
		EXPECT_EQ(0, ApplicationEventTests::window_close_n);

		trac::event_dispatch(e_window_focus);
		EXPECT_EQ(0, ApplicationEventTests::window_focus_n);

		trac::event_dispatch(e_window_lost_focus);
		EXPECT_EQ(0, ApplicationEventTests::window_lost_focus_n);

		trac::event_dispatch(e_window_resize);
		EXPECT_EQ(0, ApplicationEventTests::window_width);

		trac::event_dispatch(e_window_moved);
		EXPECT_EQ(0, ApplicationEventTests::window_pos_x);

		trac::event_dispatch(e_app_tick);
		EXPECT_EQ(0, ApplicationEventTests::ticks_n);

		trac::event_dispatch(e_app_update);
		EXPECT_EQ(0, ApplicationEventTests::updates_n);

		trac::event_dispatch(e_app_render);
		EXPECT_EQ(0, ApplicationEventTests::renders_n);

		trac::event_queue_process();
		EXPECT_EQ(0, ApplicationEventTests::window_close_n);
		EXPECT_EQ(0, ApplicationEventTests::window_focus_n);
		EXPECT_EQ(0, ApplicationEventTests::window_lost_focus_n);
		EXPECT_EQ(0, ApplicationEventTests::window_width);
		EXPECT_EQ(0, ApplicationEventTests::window_height);
		EXPECT_EQ(0, ApplicationEventTests::window_pos_x);
		EXPECT_EQ(0, ApplicationEventTests::window_pos_y);
		EXPECT_EQ(0, ApplicationEventTests::ticks_n);
		EXPECT_EQ(0, ApplicationEventTests::updates_n);
		EXPECT_EQ(0, ApplicationEventTests::renders_n);

		// Add listeners and dispatch events again
		trac::event_add_listener_b(trac::EventType::kWindowClose, ApplicationEventTests::window_close_cb_b);
		trac::event_add_listener_nb(trac::EventType::kWindowClose, ApplicationEventTests::window_close_cb_nb);
		trac::event_add_listener_b(trac::EventType::kWindowFocus, ApplicationEventTests::window_focus_cb_b);
		trac::event_add_listener_nb(trac::EventType::kWindowFocus, ApplicationEventTests::window_focus_cb_nb);
		trac::event_add_listener_b(trac::EventType::kWindowLostFocus, ApplicationEventTests::window_lost_focus_cb_b);
		trac::event_add_listener_nb(trac::EventType::kWindowLostFocus, ApplicationEventTests::window_lost_focus_cb_nb);
		trac::event_add_listener_b(trac::EventType::kWindowResize, ApplicationEventTests::window_resize_cb_b);
		trac::event_add_listener_nb(trac::EventType::kWindowResize, ApplicationEventTests::window_resize_cb_nb);
		trac::event_add_listener_b(trac::EventType::kWindowMoved, ApplicationEventTests::window_moved_cb_b);
		trac::event_add_listener_nb(trac::EventType::kWindowMoved, ApplicationEventTests::window_moved_cb_nb);
		trac::event_add_listener_b(trac::EventType::kAppTick, ApplicationEventTests::tick_cb_b);
		trac::event_add_listener_nb(trac::EventType::kAppTick, ApplicationEventTests::tick_cb_nb);
		trac::event_add_listener_b(trac::EventType::kAppUpdate, ApplicationEventTests::update_cb_b);
		trac::event_add_listener_nb(trac::EventType::kAppUpdate, ApplicationEventTests::update_cb_nb);
		trac::event_add_listener_b(trac::EventType::kAppRender, ApplicationEventTests::render_cb_b);
		trac::event_add_listener_nb(trac::EventType::kAppRender, ApplicationEventTests::render_cb_nb);

		trac::event_dispatch(e_window_close);
		EXPECT_EQ(1, ApplicationEventTests::window_close_n);

		trac::event_dispatch(e_window_focus);
		EXPECT_EQ(1, ApplicationEventTests::window_focus_n);

		trac::event_dispatch(e_window_lost_focus);
		EXPECT_EQ(1, ApplicationEventTests::window_lost_focus_n);

		trac::event_dispatch(e_window_resize);
		EXPECT_EQ(1920, ApplicationEventTests::window_width);
		EXPECT_EQ(1080, ApplicationEventTests::window_height);

		trac::event_dispatch(e_window_moved);
		EXPECT_EQ(10, ApplicationEventTests::window_pos_x);
		EXPECT_EQ(20, ApplicationEventTests::window_pos_y);

		trac::event_dispatch(e_app_tick);
		EXPECT_EQ(1, ApplicationEventTests::ticks_n);

		trac::event_dispatch(e_app_update);
		EXPECT_EQ(1, ApplicationEventTests::updates_n);

		trac::event_dispatch(e_app_render);
		EXPECT_EQ(1, ApplicationEventTests::renders_n);

		trac::event_queue_process();
		EXPECT_EQ(2, ApplicationEventTests::window_close_n);
		EXPECT_EQ(2, ApplicationEventTests::window_focus_n);
		EXPECT_EQ(2, ApplicationEventTests::window_lost_focus_n);
		EXPECT_EQ(1920, ApplicationEventTests::window_width);
		EXPECT_EQ(1080, ApplicationEventTests::window_height);
		EXPECT_EQ(10, ApplicationEventTests::window_pos_x);
		EXPECT_EQ(20, ApplicationEventTests::window_pos_y);
		EXPECT_EQ(2, ApplicationEventTests::ticks_n);
		EXPECT_EQ(2, ApplicationEventTests::updates_n);
		EXPECT_EQ(2, ApplicationEventTests::renders_n);
	}
#endif

	GTEST_TEST(tractor, events_key_blocking)
	{
		trac::initialize_engine();
		KeyEventTests::reset();

		trac::EventKeyPressed e_key_press(trac::KeyCode::SDLK_a);
		trac::EventKeyReleased e_key_release(trac::KeyCode::SDLK_b);
		trac::EventKeyTyped e_key_type(trac::KeyCode::SDLK_c);

		// Dispatching events should do nothing without listeners
		trac::event_dispatch_b(e_key_press);
		EXPECT_EQ(0, KeyEventTests::presses_n);
		EXPECT_EQ(trac::KeyCode::SDLK_UNKNOWN, KeyEventTests::last_key);

		trac::event_dispatch_b(e_key_release);
		EXPECT_EQ(0, KeyEventTests::releases_n);
		EXPECT_EQ(trac::KeyCode::SDLK_UNKNOWN, KeyEventTests::last_key);

		trac::event_dispatch_b(e_key_type);
		EXPECT_EQ(0, KeyEventTests::typed_n);
		EXPECT_EQ(trac::KeyCode::SDLK_UNKNOWN, KeyEventTests::last_key);

		// Add listeners and dispatch events
		trac::event_add_listener_b(trac::EventType::kKeyPressed, KeyEventTests::press_cb_b);
		trac::event_add_listener_b(trac::EventType::kKeyReleased, KeyEventTests::release_cb_b);
		trac::event_add_listener_b(trac::EventType::kKeyTyped, KeyEventTests::typed_cb_b);

		trac::event_dispatch_b(e_key_press);
		EXPECT_EQ(1, KeyEventTests::presses_n);
		EXPECT_EQ(trac::KeyCode::SDLK_a, KeyEventTests::last_key);

		trac::event_dispatch_b(e_key_release);
		EXPECT_EQ(1, KeyEventTests::releases_n);
		EXPECT_EQ(trac::KeyCode::SDLK_b, KeyEventTests::last_key);

		trac::event_dispatch_b(e_key_type);
		EXPECT_EQ(1, KeyEventTests::typed_n);
		EXPECT_EQ(trac::KeyCode::SDLK_c, KeyEventTests::last_key);
	}

	GTEST_TEST(tractor, events_key_non_blocking)
	{
		trac::initialize_engine();
		KeyEventTests::reset();

		std::shared_ptr<trac::Event> e_key_press = std::make_shared<trac::EventKeyPressed>(trac::KeyCode::SDLK_a);
		std::shared_ptr<trac::Event> e_key_release = std::make_shared<trac::EventKeyReleased>(trac::KeyCode::SDLK_b);
		std::shared_ptr<trac::Event> e_key_type = std::make_shared<trac::EventKeyTyped>(trac::KeyCode::SDLK_c);

		// Dispatching events should do nothing without listeners
		trac::event_dispatch_nb(e_key_press);
		EXPECT_EQ(0, KeyEventTests::presses_n);
		EXPECT_EQ(trac::KeyCode::SDLK_UNKNOWN, KeyEventTests::last_key);

		trac::event_dispatch_nb(e_key_release);
		EXPECT_EQ(0, KeyEventTests::releases_n);
		EXPECT_EQ(trac::KeyCode::SDLK_UNKNOWN, KeyEventTests::last_key);

		trac::event_dispatch_nb(e_key_type);
		EXPECT_EQ(0, KeyEventTests::typed_n);
		EXPECT_EQ(trac::KeyCode::SDLK_UNKNOWN, KeyEventTests::last_key);

		trac::event_queue_process();
		EXPECT_EQ(0, KeyEventTests::presses_n);
		EXPECT_EQ(0, KeyEventTests::releases_n);
		EXPECT_EQ(0, KeyEventTests::typed_n);

		// Add listeners and dispatch events
		trac::event_add_listener_nb(trac::EventType::kKeyPressed, KeyEventTests::press_cb_nb);
		trac::event_add_listener_nb(trac::EventType::kKeyReleased, KeyEventTests::release_cb_nb);
		trac::event_add_listener_nb(trac::EventType::kKeyTyped, KeyEventTests::typed_cb_nb);

		trac::event_dispatch_nb(e_key_press);
		EXPECT_EQ(0, KeyEventTests::presses_n);
		EXPECT_EQ(trac::KeyCode::SDLK_UNKNOWN, KeyEventTests::last_key);

		trac::event_dispatch_nb(e_key_release);
		EXPECT_EQ(0, KeyEventTests::releases_n);
		EXPECT_EQ(trac::KeyCode::SDLK_UNKNOWN, KeyEventTests::last_key);

		trac::event_dispatch_nb(e_key_type);
		EXPECT_EQ(0, KeyEventTests::typed_n);
		EXPECT_EQ(trac::KeyCode::SDLK_UNKNOWN, KeyEventTests::last_key);

		trac::event_queue_process();
		EXPECT_EQ(1, KeyEventTests::presses_n);
		EXPECT_EQ(1, KeyEventTests::releases_n);
		EXPECT_EQ(1, KeyEventTests::typed_n);
		EXPECT_EQ(trac::KeyCode::SDLK_c, KeyEventTests::last_key);
	}

	GTEST_TEST(tractor, events_mouse_blocking)
	{
		trac::initialize_engine();
		MouseEventTests::reset();

		trac::EventMouseButtonPress e_mouse_press(trac::MouseCode::kLeft);
		trac::EventMouseButtonRelease e_mouse_release(trac::MouseCode::kRight);
		trac::EventMouseMovement e_mouse_move(10.0f, 20.0f);
		trac::EventMouseScrolled e_mouse_scroll(1.0f, 2.0f);

		// Dispatching events should do nothing without listeners
		trac::event_dispatch_b(e_mouse_press);
		EXPECT_EQ(0, MouseEventTests::presses_n);
		EXPECT_EQ(trac::MouseCode::kUnknown, MouseEventTests::last_button);

		trac::event_dispatch_b(e_mouse_release);
		EXPECT_EQ(0, MouseEventTests::releases_n);
		EXPECT_EQ(trac::MouseCode::kUnknown, MouseEventTests::last_button);

		trac::event_dispatch_b(e_mouse_move);
		EXPECT_EQ(0.0f, MouseEventTests::pos_x);
		EXPECT_EQ(0.0f, MouseEventTests::pos_y);

		trac::event_dispatch_b(e_mouse_scroll);
		EXPECT_EQ(0.0f, MouseEventTests::scroll_x);
		EXPECT_EQ(0.0f, MouseEventTests::scroll_y);

		// Add listeners and dispatch events
		trac::event_add_listener_b(trac::EventType::kMouseButtonPressed, MouseEventTests::press_cb_b);
		trac::event_add_listener_b(trac::EventType::kMouseButtonReleased, MouseEventTests::release_cb_b);
		trac::event_add_listener_b(trac::EventType::kMouseMoved, MouseEventTests::move_cb_b);
		trac::event_add_listener_b(trac::EventType::kMouseScrolled, MouseEventTests::scroll_cb_b);

		trac::event_dispatch_b(e_mouse_press);
		EXPECT_EQ(1, MouseEventTests::presses_n);
		EXPECT_EQ(trac::MouseCode::kLeft, MouseEventTests::last_button);

		trac::event_dispatch_b(e_mouse_release);
		EXPECT_EQ(1, MouseEventTests::releases_n);
		EXPECT_EQ(trac::MouseCode::kRight, MouseEventTests::last_button);

		trac::event_dispatch_b(e_mouse_move);
		EXPECT_EQ(10.0f, MouseEventTests::pos_x);
		EXPECT_EQ(20.0f, MouseEventTests::pos_y);

		trac::event_dispatch_b(e_mouse_scroll);
		EXPECT_EQ(1.0f, MouseEventTests::scroll_x);
		EXPECT_EQ(2.0f, MouseEventTests::scroll_y);
	}

	GTEST_TEST(tractor, events_mouse_non_blocking)
	{
		trac::initialize_engine();
		MouseEventTests::reset();

		std::shared_ptr<trac::Event> e_mouse_press = std::make_shared<trac::EventMouseButtonPress>(trac::MouseCode::kLeft);
		std::shared_ptr<trac::Event> e_mouse_release = std::make_shared<trac::EventMouseButtonRelease>(trac::MouseCode::kRight);
		std::shared_ptr<trac::Event> e_mouse_move = std::make_shared<trac::EventMouseMovement>(10.0f, 20.0f);
		std::shared_ptr<trac::Event> e_mouse_scroll = std::make_shared<trac::EventMouseScrolled>(1.0f, 2.0f);

		// Dispatching events should do nothing without listeners
		trac::event_dispatch_nb(e_mouse_press);
		EXPECT_EQ(0, MouseEventTests::presses_n);
		EXPECT_EQ(trac::MouseCode::kUnknown, MouseEventTests::last_button);

		trac::event_dispatch_nb(e_mouse_release);
		EXPECT_EQ(0, MouseEventTests::releases_n);
		EXPECT_EQ(trac::MouseCode::kUnknown, MouseEventTests::last_button);

		trac::event_dispatch_nb(e_mouse_move);
		EXPECT_EQ(0.0f, MouseEventTests::pos_x);
		EXPECT_EQ(0.0f, MouseEventTests::pos_y);

		trac::event_dispatch_nb(e_mouse_scroll);
		EXPECT_EQ(0.0f, MouseEventTests::scroll_x);
		EXPECT_EQ(0.0f, MouseEventTests::scroll_y);

		trac::event_queue_process();
		EXPECT_EQ(0, MouseEventTests::presses_n);
		EXPECT_EQ(trac::MouseCode::kUnknown, MouseEventTests::last_button);
		EXPECT_EQ(0, MouseEventTests::releases_n);
		EXPECT_EQ(trac::MouseCode::kUnknown, MouseEventTests::last_button);
		EXPECT_EQ(0.0f, MouseEventTests::pos_x);
		EXPECT_EQ(0.0f, MouseEventTests::pos_y);
		EXPECT_EQ(0.0f, MouseEventTests::scroll_x);
		EXPECT_EQ(0.0f, MouseEventTests::scroll_y);

		// Add listeners
		trac::event_add_listener_nb(trac::EventType::kMouseButtonPressed, MouseEventTests::press_cb_nb);
		trac::event_add_listener_nb(trac::EventType::kMouseButtonReleased, MouseEventTests::release_cb_nb);
		trac::event_add_listener_nb(trac::EventType::kMouseMoved, MouseEventTests::move_cb_nb);
		trac::event_add_listener_nb(trac::EventType::kMouseScrolled, MouseEventTests::scroll_cb_nb);

		// Dispatch events, since they are non-blocking, they should not do anything before processed.
		trac::event_dispatch_nb(e_mouse_press);
		EXPECT_EQ(0, MouseEventTests::presses_n);
		EXPECT_EQ(trac::MouseCode::kUnknown, MouseEventTests::last_button);

		trac::event_dispatch_nb(e_mouse_release);
		EXPECT_EQ(0, MouseEventTests::releases_n);
		EXPECT_EQ(trac::MouseCode::kUnknown, MouseEventTests::last_button);

		trac::event_dispatch_nb(e_mouse_move);
		EXPECT_EQ(0.0f, MouseEventTests::pos_x);
		EXPECT_EQ(0.0f, MouseEventTests::pos_y);

		trac::event_dispatch_nb(e_mouse_scroll);
		EXPECT_EQ(0.0f, MouseEventTests::scroll_x);
		EXPECT_EQ(0.0f, MouseEventTests::scroll_y);

		// Process events
		trac::event_queue_process();

		EXPECT_EQ(1, MouseEventTests::presses_n);
		EXPECT_EQ(1, MouseEventTests::releases_n);
		// Since all events are processed in order, the last button should be the last one dispatched
		EXPECT_EQ(trac::MouseCode::kRight, MouseEventTests::last_button);
		EXPECT_EQ(10.0f, MouseEventTests::pos_x);
		EXPECT_EQ(20.0f, MouseEventTests::pos_y);
		EXPECT_EQ(1.0f, MouseEventTests::scroll_x);
		EXPECT_EQ(2.0f, MouseEventTests::scroll_y);
	}
} // namespace test