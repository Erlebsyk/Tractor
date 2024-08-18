/**
 * @file layer.cpp
 * @brief Source file for the layer module, see layer.hpp for more information.
 * 
 * @author Erlend Elias Isachsen
 * */

/** Tractor PCH */
#include "tractor_pch.hpp"

/** Includes	*/
#include "layer.hpp"
#include "events.hpp"
#include "logger.hpp"

/** Definitions	*/

namespace trac
{	
	/**
	 * @brief Construct a new instance of Layer.
	 * 
	 * @param name The name of the layer (only used in debug builds).
	 */
	Layer::Layer(const std::string name) :
		attached_		{ false	},
#ifdef TRAC_DEBUG
		dbg_name_		{ name	}
#endif
	{}

	/// @brief Function to run on layer attach.
	void Layer::OnAttach()
	{
		if(!attached_)
		{
			attached_ = true;
			log_engine_debug("Layer::OnAttach: Layer attached: {0}", GetName());
		}
	}

	/// @brief Function to run on layer detach.
	void Layer::OnDetach()
	{
		if(attached_)
		{
			attached_ = false;
			log_engine_debug("Layer::OnDetach: Layer detached: {0}", GetName());
		}
	}

	/// @brief Function to run on layer update.
	void Layer::OnUpdate()
	{

	}

	/**
	 * @brief Handles events pushed to the layer.
	 * 
	 * @param event 
	 */
	void Layer::OnEvent(Event& event)
	{
		switch(event.GetType())
		{
			case EventType::kLayerAttached:
				OnAttach();
				break;
			case EventType::kLayerDetached:
				OnDetach();
				break;
			case EventType::kLayerUpdated:
				OnUpdate();
				break;
			default:
				break;
		}
	}

	/**
	 * @brief Get the name of the layer. Only returns a value in debug builds.
	 * 
	 * @return std::string The layer name.
	 * @retval "" If not in debug mode.
	 */
	std::string Layer::GetName() const
	{
#ifdef TRAC_DEBUG
		return dbg_name_;
#else
		return "";
#endif
	}


} // Namespace trac