/**
 * @file layer_stack.cpp
 * @brief Source file for the layer stack module, see layer_stack.hpp for more information.
 * 
 * @author Erlend Elias Isachsen
 * */

/** Tractor PCH */
#include "tractor_pch.hpp"

/** Includes	*/
#include "layer_stack.hpp"

/** Definitions	*/

namespace trac
{
	/**
	 * @brief	Pushed a new layer into the stack. The layer will be appended to the end of the layer stack,
	 * 			but before any overlays.
	 * 
	 * @param layer	The layer to push.
	 */
	void LayerStack::PushLayer(std::shared_ptr<Layer> layer)
	{
		layer_insert_ = layers_.emplace(layer_insert_, layer);
	}

	/**
	 * @brief Removes a layer from the stack.
	 * 
	 * @param layer	The layer to remove.
	 */
	void LayerStack::PopLayer(std::shared_ptr<Layer> layer)
	{
		trac::layer_vector_t::iterator it = std::find(layers_.begin(), layers_.end(), layer);
		if(it != layers_.end())
		{
			layers_.erase(it);
			layer_insert_--;
		}
	}

	/**
	 * @brief Pushes an overlay onto the layer stack. The overlay will be appended to the very end of the layer stack.
	 * 
	 * @param overlay	The overlay to push.
	 */
	void LayerStack::PushOverlay(std::shared_ptr<Layer> overlay)
	{
		layers_.emplace_back(overlay);
	}

	/**
	 * @brief Pops an overlay from the layer stack.
	 * 
	 * @param overlay	The overlay to pop.
	 */
	void LayerStack::PopOverlay(std::shared_ptr<Layer> overlay)
	{
		trac::layer_vector_t::iterator it = std::find(layers_.begin(), layers_.end(), overlay);
		if(it != layers_.end())
		{
			layers_.erase(it);
		}
	}

	/**
	 * @brief Get the begin iterator for the layer stack. This will point to the first layer in the stack.
	 * 
	 * @return layer_vector_t::iterator	The begin iterator for the layer stack.
	 */
	layer_vector_t::iterator LayerStack::begin()
	{
		return layers_.begin();
	}

	/**
	 * @brief Get the end iterator for the layer stack.
	 * 
	 * @return layer_vector_t::iterator	The end iterator for the layer stack.
	 */
	layer_vector_t::iterator LayerStack::end()
	{
		return layers_.end();
	}

} // Namespace trac