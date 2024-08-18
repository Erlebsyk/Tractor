/**
 * @file layer.hpp
 * @brief Module for handling layers.
 * 
 * @author Erlend Elias Isachsen (erlend@isachsen.org)
 */

#ifndef LAYER_HPP_
#define LAYER_HPP_

/** Includes	*/
#include <cstdint>
#include <string>

#include "events.hpp"

/** Definitions	*/

namespace trac
{
	/// @brief A layer class that can be used to create layers in the application.
	class Layer
	{
	public:
		Layer() = default;
		Layer(std::string name);
		virtual ~Layer() = default;

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();

		virtual void OnEvent(Event& event);

		std::string GetName() const;

	protected:
		/// Whether the layer is attached to the application or not.
		bool attached_; 
#ifdef TRAC_DEBUG
		/// The name of the layer, only used in debug builds.
		const std::string dbg_name_;
#endif
	};


} // Namespace trac

#endif /* LAYER_HPP_ */