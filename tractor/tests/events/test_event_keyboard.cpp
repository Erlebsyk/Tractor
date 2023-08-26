// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// Add test event data
#include "test_event_data.hpp"

namespace test
{
	static void event_keyboard_cb(std::shared_ptr<trac::Event> e);
	static void event_keyboard_text_cb(std::shared_ptr<trac::Event> e);
	static void event_keyboard_text_editing_cb(std::shared_ptr<trac::Event> e);

	struct KeyboardData
	{
		trac::KeySym key_sym = trac::KeySym();
		trac::window_id_t window_id = 0;
		bool repeat = false;
	};

	struct KeyboardTextData
	{
		std::string text = "";
	};

	struct KeyboardTextEditingData
	{
		size_t start = 0;
		size_t length = 0;
	};

	class EventKeyboardData : public EventBaseData
	{
	public:
		EventKeyboardData() : 
			EventBaseData(),
			keyboard_data_ {},
			keyboard_text_data_ {},
			keyboard_text_edit_data_ {}
		{}

		void Set(std::shared_ptr<trac::Event> e) override
		{
			EventBaseData::Set(e);

			auto event_keyboard = std::static_pointer_cast<trac::EventKeyboard>(e);
			keyboard_data_.key_sym = event_keyboard->GetKeySym();
			keyboard_data_.window_id = event_keyboard->GetWindowId();
			keyboard_data_.repeat = event_keyboard->IsRepeat();
		}

		void SetTextData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_text = std::static_pointer_cast<trac::EventText>(e);
			keyboard_text_data_.text = event_text->GetText();
		}

		void SetTextEditingData(std::shared_ptr<trac::Event> e)
		{
			Set(e);
			auto event_text_edit = std::static_pointer_cast<trac::EventTextEditing>(e);
			keyboard_text_edit_data_.start = event_text_edit->GetStart();
			keyboard_text_edit_data_.length = event_text_edit->GetLength();
		}

		KeyboardData GetKeyboardData() const { return keyboard_data_; }
		KeyboardTextData GetKeyboardTextData() const { return keyboard_text_data_; }
		KeyboardTextEditingData GetKeyboardTextEditingData() const { return keyboard_text_edit_data_; }

	private:
		KeyboardData keyboard_data_;
		KeyboardTextData keyboard_text_data_;
		KeyboardTextEditingData keyboard_text_edit_data_;
	};

	static EventKeyboardData data_g = EventKeyboardData();

	void event_keyboard_cb(std::shared_ptr<trac::Event> e) { data_g.Set(e); }
	void event_keyboard_text_cb(std::shared_ptr<trac::Event> e) { data_g.SetTextData(e); }
	void event_keyboard_text_editing_cb(std::shared_ptr<trac::Event> e) { data_g.SetTextEditingData(e); }

	GTEST_TEST(tractor, event_keyboard)
	{
		trac::event_listener_remove_all();

		// Initial values should be blank / zero
		data_g = EventKeyboardData();
		EXPECT_STREQ("", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, data_g.GetType());
		EXPECT_EQ(trac::EventCategory::kNone, data_g.GetCategoryFlags());
		EXPECT_EQ(0, data_g.GetTimestampMs());
		EXPECT_STREQ("", data_g.GetString().c_str());
		EXPECT_EQ(nullptr, data_g.GetEvent());
		EXPECT_EQ(SDL_Scancode::SDL_SCANCODE_UNKNOWN, data_g.GetKeyboardData().key_sym.scancode);
		EXPECT_EQ(SDL_KeyCode::SDLK_UNKNOWN, data_g.GetKeyboardData().key_sym.keycode);
		EXPECT_EQ(0, data_g.GetKeyboardData().key_sym.mod);
		EXPECT_EQ(0, data_g.GetKeyboardData().window_id);
		EXPECT_FALSE(data_g.GetKeyboardData().repeat);
		EXPECT_STREQ("", data_g.GetKeyboardTextData().text.c_str());
		EXPECT_EQ(0, data_g.GetKeyboardTextEditingData().start);
		EXPECT_EQ(0, data_g.GetKeyboardTextEditingData().length);

		// Register all event listeners
		trac::event_listener_add_nb(trac::EventType::kKeyDown, event_keyboard_cb);
		trac::event_listener_add_nb(trac::EventType::kKeyUp, event_keyboard_cb);
		trac::event_listener_add_nb(trac::EventType::kTextEditing, event_keyboard_text_editing_cb);
		trac::event_listener_add_nb(trac::EventType::kTextInput, event_keyboard_text_cb);
		trac::event_listener_add_nb(trac::EventType::kKeyMapChanged, event_keyboard_cb);

		// Create a shared pointer to an event
		std::shared_ptr<trac::Event> e;
		trac::timestamp_t timestamp_ms = 0;

		// Dispatch each event type one by one
		data_g = EventKeyboardData();
		e = std::make_shared<trac::EventKeyboardDown>(trac::KeySym(SDL_Scancode::SDL_SCANCODE_A, SDL_KeyCode::SDLK_a, 0), 1, true);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventKeyboardDown", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kKeyDown, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kKeyboard | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventKeyboardDown: [1, 4 (97), 0, true]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(SDL_Scancode::SDL_SCANCODE_A, data_g.GetKeyboardData().key_sym.scancode);
		EXPECT_EQ(SDL_KeyCode::SDLK_a, data_g.GetKeyboardData().key_sym.keycode);
		EXPECT_EQ(0, data_g.GetKeyboardData().key_sym.mod);
		EXPECT_EQ(1, data_g.GetKeyboardData().window_id);
		EXPECT_TRUE(data_g.GetKeyboardData().repeat);
		
		data_g = EventKeyboardData();
		e = std::make_shared<trac::EventKeyboardUp>(trac::KeySym(SDL_Scancode::SDL_SCANCODE_B, SDL_KeyCode::SDLK_b, 1), 2);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventKeyboardUp", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kKeyUp, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kKeyboard | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventKeyboardUp: [2, 5 (98), 1, false]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(SDL_Scancode::SDL_SCANCODE_B, data_g.GetKeyboardData().key_sym.scancode);
		EXPECT_EQ(SDL_KeyCode::SDLK_b, data_g.GetKeyboardData().key_sym.keycode);
		EXPECT_EQ(1, data_g.GetKeyboardData().key_sym.mod);
		EXPECT_EQ(2, data_g.GetKeyboardData().window_id);
		EXPECT_FALSE(data_g.GetKeyboardData().repeat);

		data_g = EventKeyboardData();
		e = std::make_shared<trac::EventTextEditing>("text editing", 3, 4, 2);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventTextEditing", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kTextEditing, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kKeyboard | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventTextEditing: [3, \"text editing\" (4, 2)]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_EQ(4, data_g.GetKeyboardTextEditingData().start);
		EXPECT_EQ(2, data_g.GetKeyboardTextEditingData().length);

		data_g = EventKeyboardData();
		e = std::make_shared<trac::EventTextInput>("text input", 4);
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventTextInput", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kTextInput, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kKeyboard | trac::EventCategory::kInput), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventTextInput: [4, \"text input\"]", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
		EXPECT_STREQ("text input", data_g.GetKeyboardTextData().text.c_str());

		data_g = EventKeyboardData();
		e = std::make_shared<trac::EventKeyMapChanged>();
		timestamp_ms = e->GetTimestampMs();
		trac::event_dispatch(e);
		trac::event_queue_process();
		EXPECT_STREQ("EventKeyMapChanged", data_g.GetName().c_str());
		EXPECT_EQ(trac::EventType::kKeyMapChanged, data_g.GetType());
		EXPECT_EQ((trac::EventCategory::kKeyboard | trac::EventCategory::kDevice), data_g.GetCategoryFlags());
		EXPECT_EQ(timestamp_ms, data_g.GetTimestampMs());
		EXPECT_STREQ("EventKeyMapChanged", data_g.GetString().c_str());
		EXPECT_EQ(e, data_g.GetEvent());
	}
} // namespace test