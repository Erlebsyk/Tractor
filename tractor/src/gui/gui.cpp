/**
 * @file gui.cpp
 * @brief Source file for the graphical user interface module of the Tractor game engine. See gui.hpp for more information.
 * 
 * @author Erlend Elias Isachsen
 */

/** Includes	*/
#include "tractor_pch.hpp"
#include "gui/gui.hpp"
#include "application.hpp"

#include "glad/glad.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif

namespace trac
{
	/// The default delta time.
	static constexpr float kDeltaTimeDefault = 1.0f / 60.0f;

	GuiLayer::GuiLayer() : 
		Layer("GuiLayer"),
		frame_time_ {0}
	{}

	void GuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		io.KeyMap[ImGuiKey_Tab] = SDL_SCANCODE_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
		io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
		io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
		io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
		io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
		io.KeyMap[ImGuiKey_Insert] = SDL_SCANCODE_INSERT;
		io.KeyMap[ImGuiKey_Delete] = SDL_SCANCODE_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = SDL_SCANCODE_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = SDL_SCANCODE_SPACE;
		io.KeyMap[ImGuiKey_Enter] = SDL_SCANCODE_RETURN;
		io.KeyMap[ImGuiKey_Escape] = SDL_SCANCODE_ESCAPE;
		io.KeyMap[ImGuiKey_A] = SDL_SCANCODE_A;
		io.KeyMap[ImGuiKey_C] = SDL_SCANCODE_C;
		io.KeyMap[ImGuiKey_V] = SDL_SCANCODE_V;
		io.KeyMap[ImGuiKey_X] = SDL_SCANCODE_X;
		io.KeyMap[ImGuiKey_Y] = SDL_SCANCODE_Y;
		io.KeyMap[ImGuiKey_Z] = SDL_SCANCODE_Z;

		ImGui::StyleColorsDark();

		Window& window = Application::Get().GetWindow();
		SDL_Window *sdl_window = static_cast<SDL_Window*>(window.GetNativeWindow());
		SDL_Renderer* renderer = window.GetRenderer();

		// Setup Platform/Renderer backends
		ImGui_ImplSDL2_InitForSDLRenderer(sdl_window, renderer);
		ImGui_ImplSDLRenderer2_Init(renderer);
	}

	void GuiLayer::OnDetach()
	{

	}

	void GuiLayer::OnUpdate()
	{
		const float time = (float)(SDL_GetTicks64()) / 1000.0f;
		ImGuiIO& io = ImGui::GetIO();
		io.DeltaTime = (frame_time_ > 0.0f) ? (time - io.DeltaTime) : kDeltaTimeDefault;
		frame_time_ = time;

		Window& window = Application::Get().GetWindow();
		SDL_Window *sdl_window = static_cast<SDL_Window*>(window.GetNativeWindow());
		SDL_Renderer* renderer = window.GetRenderer();

        if (SDL_GetWindowFlags(sdl_window) & SDL_WINDOW_MINIMIZED)
		{
			SDL_Delay(10);
            return;
		}

		// Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		

		ImGui::Render();
		//SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
		//SDL_SetRenderDrawColor(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
		int status = SDL_RenderClear(renderer);
		if(status != 0)
			log_engine_error("Error: SDL_RenderClear(): {0}", SDL_GetError());

		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
		SDL_RenderPresent(renderer);
	}

	void GuiLayer::OnEvent(Event& event)
	{

	}

} // Namespace trac