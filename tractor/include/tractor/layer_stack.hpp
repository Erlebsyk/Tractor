/**
 * @file layer_stack.hpp
 * @brief Layer stack module for the tractor game engine.
 * 
 * @author Erlend Elias Isachsen
 */

#ifndef LAYER_STACK_HPP_
#define LAYER_STACK_HPP_

/** Includes	*/
#include <cstdint>

#include "layer.hpp"

/** Definitions	*/

namespace trac
{
	/// Layer vector type. Vector of shared pointers to layers.
	typedef std::vector<std::shared_ptr<Layer>> layer_vector_t;
	/// Layer iterator type.
	typedef layer_vector_t::iterator layer_iterator_t;

	/// @brief A layer stack class that can be used to create layer stacks in the application.
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack() = default;

		void PushLayer(std::shared_ptr<Layer> layer);
		void PopLayer(std::shared_ptr<Layer> layer);

		void PushOverlay(std::shared_ptr<Layer> overlay);
		void PopOverlay(std::shared_ptr<Layer> overlay);

		layer_iterator_t begin();
		layer_iterator_t end();

	private:
		// A vector of the layers in the stack.
		layer_vector_t layers_;
		// An iterator to the layer insert position. At the end of normal layers, but before overlays.
		layer_iterator_t layer_insert_;
	};
} // Namespace trac

#endif /* LAYER_STACK_HPP_ */