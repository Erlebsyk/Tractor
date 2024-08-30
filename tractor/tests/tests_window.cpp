// Google Test Framework
#include <gtest/gtest.h>

// Standard library header includes
#include <memory>

// Related header include
#include <tractor/window.hpp>

namespace test
{
	GTEST_TEST(tractor, basic_window_open_close)
	{
		// Create a window with default properties
		std::unique_ptr<trac::Window> window = trac::Window::Create();

		// Check if the window is open
		EXPECT_TRUE(window->IsOpen());

		// Close the window
		window->Close();

		// Check if the window is closed
		EXPECT_FALSE(window->IsOpen());
	}

	GTEST_TEST(tractor, basic_window_show_hide)
	{
		// Create a window with default properties
		std::unique_ptr<trac::Window> window = trac::Window::Create();

		EXPECT_TRUE(window->IsOpen());
		EXPECT_TRUE(window->IsVisible());

		window->Hide();
		EXPECT_FALSE(window->IsVisible());
		window->Show();
		EXPECT_TRUE(window->IsVisible());

		window->Close();
		EXPECT_FALSE(window->IsOpen());
		EXPECT_FALSE(window->IsVisible());

		window->Open();
		EXPECT_TRUE(window->IsOpen());

		window->Close();
	}

	/// @brief  Test the window Vsync functionality.
	GTEST_TEST(tractor, basic_window_vsync)
	{
		// Create a window with default properties
		std::unique_ptr<trac::Window> window = trac::Window::Create();

		EXPECT_TRUE(window->IsOpen());

		window->SetVsync(true);
		EXPECT_TRUE(window->IsVsyncEnabled());
		window->SetVsync(false);
		EXPECT_FALSE(window->IsVsyncEnabled());

		window->Close();
		EXPECT_FALSE(window->IsOpen());
	}

	/// @brief  Test the window default properties.
	GTEST_TEST(tractor, default_window_properties)
	{
		// Create a window with default properties
		std::unique_ptr<trac::Window> window = trac::Window::Create();
		EXPECT_TRUE(window->IsOpen());

		EXPECT_EQ(window->GetTitle(), trac::WindowPropertiesDefault::kTitle);
		EXPECT_EQ(window->GetWidth(), trac::WindowPropertiesDefault::kWidth);
		EXPECT_EQ(window->GetHeight(), trac::WindowPropertiesDefault::kHeight);
		EXPECT_EQ(window->GetX(), trac::WindowPropertiesDefault::kPosX);
		EXPECT_EQ(window->GetY(), trac::WindowPropertiesDefault::kPosY);
		EXPECT_EQ(window->IsVsyncEnabled(), trac::WindowPropertiesDefault::kVsync);
		EXPECT_EQ(window->IsResizable(), trac::WindowPropertiesDefault::kResizable);
		EXPECT_EQ(window->IsBorderless(), trac::WindowPropertiesDefault::kBorderless);
		EXPECT_EQ(window->IsFullscreen(), trac::WindowPropertiesDefault::kFullscreen);
		EXPECT_EQ(window->IsVisible(), trac::WindowPropertiesDefault::kVisible);
		EXPECT_EQ(window->IsMinimized(), trac::WindowPropertiesDefault::kMinimized);
		EXPECT_EQ(window->IsMaximized(), trac::WindowPropertiesDefault::kMaximized);
		EXPECT_EQ(window->IsHighDPI(), trac::WindowPropertiesDefault::kHighDPI);
		EXPECT_EQ(window->IsAlwaysOnTop(), trac::WindowPropertiesDefault::kAlwaysOnTop);
		EXPECT_EQ(window->IsKeyboardGrabbed(), trac::WindowPropertiesDefault::kKeyboardGrabbed);
		EXPECT_EQ(window->IsInputGrabbed(), trac::WindowPropertiesDefault::kInputGrabbed);

		window->Close();
		EXPECT_FALSE(window->IsOpen());
	}

	GTEST_TEST(tractor, window_properties)
	{
		// Create a window with custom properties
		std::unique_ptr<trac::Window> window = trac::Window::Create(trac::WindowProperties(
			"Test Window",	// Title
			800,			// Width
			600,			// Height
			10,				// Position X
			20,				// Position Y
			true,			// VSync
			false,			// Resizable
			false,			// Borderless
			false,			// Fullscreen
			true,			// Visible
			false,			// Minimized
			false,			// Maximized
			true,			// Input focus
			true,			// High DPI
			true,			// Always on top
			true, 			// Keyboard grab
			true			// Input grab
		));

		EXPECT_TRUE(window->IsOpen());
		EXPECT_EQ(window->GetTitle(), "Test Window");
		EXPECT_EQ(window->GetWidth(), 800);
		EXPECT_EQ(window->GetHeight(), 600);
		EXPECT_EQ(window->GetX(), 10);
		EXPECT_EQ(window->GetY(), 20);
		EXPECT_TRUE(window->IsVsyncEnabled());
		EXPECT_FALSE(window->IsResizable());
		EXPECT_FALSE(window->IsBorderless());
		EXPECT_FALSE(window->IsFullscreen());
		EXPECT_TRUE(window->IsVisible());
		EXPECT_FALSE(window->IsMinimized());
		EXPECT_FALSE(window->IsMaximized());
		EXPECT_TRUE(window->IsHighDPI());
		EXPECT_TRUE(window->IsAlwaysOnTop());
		EXPECT_TRUE(window->IsKeyboardGrabbed());
		EXPECT_TRUE(window->IsInputGrabbed());
		

		// Change one setting at a time and check if it is changed
		window->SetTitle("Test Window 2");
		EXPECT_EQ(window->GetTitle(), "Test Window 2");

		window->SetWidth(1024);
		EXPECT_EQ(window->GetWidth(), 1024);
		window->SetHeight(768);
		EXPECT_EQ(window->GetHeight(), 768);
		window->SetX(30);
		EXPECT_EQ(window->GetX(), 30);
		window->SetY(40);
		EXPECT_EQ(window->GetY(), 40);
		window->SetVsync(false);
		EXPECT_FALSE(window->IsVsyncEnabled());
		window->SetResizable(true);
		EXPECT_TRUE(window->IsResizable());
		window->SetBorderless(true);
		EXPECT_TRUE(window->IsBorderless());
		window->SetFullscreen(true);
		EXPECT_TRUE(window->IsFullscreen());
		window->SetFullscreen(false);
		EXPECT_FALSE(window->IsFullscreen());
		window->SetVisibility(false);
		EXPECT_FALSE(window->IsVisible());
		window->SetVisibility(true);
		EXPECT_TRUE(window->IsVisible());
		window->SetMinimized(true);
		EXPECT_TRUE(window->IsMinimized());
		window->SetMinimized(false);
		EXPECT_FALSE(window->IsMinimized());
		window->SetMaximized(true);
		EXPECT_TRUE(window->IsMaximized());
		window->SetMaximized(false);
		EXPECT_FALSE(window->IsMaximized());
		window->SetAlwaysOnTop(true);
		EXPECT_TRUE(window->IsAlwaysOnTop());
		window->SetAlwaysOnTop(false);
		EXPECT_FALSE(window->IsAlwaysOnTop());
		window->SetInputGrabbed(true);
		EXPECT_TRUE(window->IsInputGrabbed());

		const uint32_t flags = window->GetStatusFlags();
		// Check if each flag is set
		EXPECT_FALSE(flags & trac::WindowStatus::kWindowFullscreen);
		EXPECT_TRUE(flags & trac::WindowStatus::kWindowVisible);
		EXPECT_TRUE(flags & trac::WindowStatus::kWindowResizable);
		EXPECT_TRUE(flags & trac::WindowStatus::kWindowBorderless);
		EXPECT_FALSE(flags & trac::WindowStatus::kWindowMinimized);
		EXPECT_FALSE(flags & trac::WindowStatus::kWindowMaximized);
		// Mouse grab - difficult to test reliably
		EXPECT_TRUE(flags & trac::WindowStatus::kWindowInputFocus);
		// Mouse focus - difficult to test reliably
		EXPECT_TRUE(flags & trac::WindowStatus::kWindowHighDPI);
		// Mouse capture - difficult to test reliably
		EXPECT_FALSE(flags & trac::WindowStatus::kWindowAlwaysOnTop);
		// Keyboard grab - difficult to test reliably
		EXPECT_TRUE(flags & trac::WindowStatus::kWindowInputGrabbed);
		EXPECT_FALSE(flags & trac::WindowStatus::kWindowVsync);
		
		// Test alternative size and position set functions
		window->SetSize(640, 480);
		EXPECT_EQ(window->GetWidth(), 640);
		EXPECT_EQ(window->GetHeight(), 480);
		window->SetPosition(50, 60);
		EXPECT_EQ(window->GetX(), 50);
		EXPECT_EQ(window->GetY(), 60);

		// Test the window close function and store properties, then reopen the window to check if the properties are restored
		window->Close(true);
		EXPECT_FALSE(window->IsOpen());

		window->Open();
		EXPECT_TRUE(window->IsOpen());
		EXPECT_EQ(window->GetTitle(), "Test Window 2");
		EXPECT_EQ(window->GetWidth(), 640);
		EXPECT_EQ(window->GetHeight(), 480);
		EXPECT_EQ(window->GetX(), 50);
		EXPECT_EQ(window->GetY(), 60);
		EXPECT_FALSE(window->IsVsyncEnabled());
		EXPECT_TRUE(window->IsResizable());
		EXPECT_TRUE(window->IsBorderless());
		EXPECT_FALSE(window->IsFullscreen());
		EXPECT_TRUE(window->IsVisible());
		EXPECT_FALSE(window->IsMinimized());
		EXPECT_FALSE(window->IsMaximized());
		EXPECT_TRUE(window->IsHighDPI());
		EXPECT_FALSE(window->IsAlwaysOnTop());
		EXPECT_TRUE(window->IsKeyboardGrabbed());
		EXPECT_TRUE(window->IsInputGrabbed());

		// Test the GetProperties function
		const trac::WindowProperties properties = window->GetProperties();
		EXPECT_EQ(properties.title, "Test Window 2");
		EXPECT_EQ(properties.width, 640);
		EXPECT_EQ(properties.height, 480);
		EXPECT_EQ(properties.pos_x, 50);
		EXPECT_EQ(properties.pos_y, 60);
		EXPECT_FALSE(properties.vsync);
		EXPECT_TRUE(properties.resizable);
		EXPECT_TRUE(properties.borderless);
		EXPECT_FALSE(properties.fullscreen);
		EXPECT_TRUE(properties.visible);
		EXPECT_FALSE(properties.minimized);
		EXPECT_FALSE(properties.maximized);
		EXPECT_TRUE(properties.input_focus);
		EXPECT_TRUE(properties.high_dpi);
		EXPECT_FALSE(properties.always_on_top);
		EXPECT_TRUE(properties.keyboard_grabbed);
		EXPECT_TRUE(properties.input_grabbed);

		// Test the shared pointer variant of the GetProperties function
		const std::shared_ptr<trac::WindowProperties> properties_shared = window->GetPropertiesPtr();
		EXPECT_EQ(properties_shared->title, "Test Window 2");
		EXPECT_EQ(properties_shared->width, 640);
		EXPECT_EQ(properties_shared->height, 480);
		EXPECT_EQ(properties_shared->pos_x, 50);
		EXPECT_EQ(properties_shared->pos_y, 60);
		EXPECT_FALSE(properties_shared->vsync);
		EXPECT_TRUE(properties_shared->resizable);
		EXPECT_TRUE(properties_shared->borderless);
		EXPECT_FALSE(properties_shared->fullscreen);
		EXPECT_TRUE(properties_shared->visible);
		EXPECT_FALSE(properties_shared->minimized);
		EXPECT_FALSE(properties_shared->maximized);
		EXPECT_TRUE(properties_shared->input_focus);
		EXPECT_TRUE(properties_shared->high_dpi);
		EXPECT_FALSE(properties_shared->always_on_top);
		EXPECT_TRUE(properties_shared->keyboard_grabbed);
		EXPECT_TRUE(properties_shared->input_grabbed);

		// Close the window without storing properties
		window->Close(false);
		EXPECT_FALSE(window->IsOpen());

		// Open the window again and check for default properties
		window->Open();
		EXPECT_TRUE(window->IsOpen());
		EXPECT_EQ(window->GetTitle(), trac::WindowPropertiesDefault::kTitle);
		EXPECT_EQ(window->GetWidth(), trac::WindowPropertiesDefault::kWidth);
		EXPECT_EQ(window->GetHeight(), trac::WindowPropertiesDefault::kHeight);
		EXPECT_EQ(window->GetX(), trac::WindowPropertiesDefault::kPosX);
		EXPECT_EQ(window->GetY(), trac::WindowPropertiesDefault::kPosY);
		EXPECT_EQ(window->IsVsyncEnabled(), trac::WindowPropertiesDefault::kVsync);
		EXPECT_EQ(window->IsResizable(), trac::WindowPropertiesDefault::kResizable);
		EXPECT_EQ(window->IsBorderless(), trac::WindowPropertiesDefault::kBorderless);
		EXPECT_EQ(window->IsFullscreen(), trac::WindowPropertiesDefault::kFullscreen);
		EXPECT_EQ(window->IsVisible(), trac::WindowPropertiesDefault::kVisible);
		EXPECT_EQ(window->IsMinimized(), trac::WindowPropertiesDefault::kMinimized);
		EXPECT_EQ(window->IsMaximized(), trac::WindowPropertiesDefault::kMaximized);
		EXPECT_EQ(window->IsHighDPI(), trac::WindowPropertiesDefault::kHighDPI);
		EXPECT_EQ(window->IsAlwaysOnTop(), trac::WindowPropertiesDefault::kAlwaysOnTop);
		EXPECT_EQ(window->IsKeyboardGrabbed(), trac::WindowPropertiesDefault::kKeyboardGrabbed);
		EXPECT_EQ(window->IsInputGrabbed(), trac::WindowPropertiesDefault::kInputGrabbed);	

		// Close the window
		window->Close();
		EXPECT_FALSE(window->IsOpen());
	}
}