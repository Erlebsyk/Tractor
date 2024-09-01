/**
 * \file gui.hpp
 * \brief GUI module for creating and interacting with graphical user interfaces for the Tractor game engine.
 * 
 * \author Erlend Elias Isachsen
 * */

#ifndef GUI_HPP_
#define GUI_HPP_

/** Includes	*/
#include <cstdint>

#include "../layer.hpp"

#include <SDL_render.h>

namespace trac
{
	/// @brief The GUI layer class.
	class GuiLayer : public Layer
	{
	public:

		GuiLayer();
		~GuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;

		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		/// The time of the last frame.
		float frame_time_;
		/// Pointer to the SDL renderer.
		SDL_Renderer* renderer;
	};

} // Namespace trac

#endif /* GUI_HPP_ */