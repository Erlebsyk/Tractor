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

	/// @brief  Test the window fullscreen functionality.
	GTEST_TEST(tractor, default_window_properties)
	{
		// Create a window with default properties
		std::unique_ptr<trac::Window> window = trac::Window::Create();

		EXPECT_TRUE(window->IsOpen());
		EXPECT_FALSE(window->IsFullscreen());
		EXPECT_TRUE(window->IsVisible());
		EXPECT_TRUE(window->IsResizable());
		EXPECT_FALSE(window->IsBorderless());
		EXPECT_FALSE(window->IsMinimized());
		EXPECT_FALSE(window->IsMaximized());
		EXPECT_FALSE(window->IsMouseGrabbed());
		EXPECT_TRUE(window->IsInputFocus());
		EXPECT_TRUE(window->IsMouseFocus());
		EXPECT_FALSE(window->IsHighDPI());
		EXPECT_FALSE(window->IsMouseCaptured());
		EXPECT_FALSE(window->IsAlwaysOnTop());
		EXPECT_FALSE(window->IsKeyboardGrabbed());
		EXPECT_FALSE(window->IsInputGrabbed());

		window->Close();
		EXPECT_FALSE(window->IsOpen());
	}
}