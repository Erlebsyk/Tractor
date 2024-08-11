/**
 * @file	test_event.cpp
 * @brief	This file contains the unit tests for the event system. These tests will check that event dispatching, listeners and the event queue works as
 * 			expected.
 * 
 * 	It is expected that dispatching blocking events explicitly will only effect blocking listeners, and that dispatching non-blocking events explicitly will
 * 	only effect non-blocking listeners. When dispatching generic events (event_dispatch), blocking listeners should be called immediately and non-blocking
 * 	listeners should be queued and processed when the event queue is processed.
 * 
 *  All functions and systems that applies to all events should be tested here, and functions that are specific to a certain event type should be tested in
 * 	their corresponding test files.
 * 
 * @author	Erlend Elias Isachsen
 * @date	22.08.2023
 */

// Google Test Framework
#include <gtest/gtest.h>

// Related header include
#include <tractor.hpp>

// Standard libary header includes
#include <memory>

namespace test
{
	class EventData
	{
	private:
		uint32_t ticks_n_;
		uint32_t renders_n_;


	public:
		EventData() : ticks_n_{ 0 }, renders_n_{ 0 } {}
		
		uint32_t GetTicks() { return ticks_n_; }
		uint32_t GetRenders() { return renders_n_; }

		void reset()
		{
			ticks_n_ = 0;
			renders_n_ = 0;
		}

		void AppTickCbB(trac::Event& e) { ticks_n_++; }
		void AppTickCbNb(std::shared_ptr<trac::Event> e) { ticks_n_++; }

		void AppRenderCbB(trac::Event& e) { renders_n_++; }
		void AppRenderCbNb(std::shared_ptr<trac::Event> e) { renders_n_++; }
	};

	/// @brief	Simple "static" test class for testing the event system.
	class EventDataStatic
	{
	private:
		static uint32_t ticks_n_;
		static uint32_t renders_n_;

		EventDataStatic(){}

	public:

		static uint32_t GetTicks() { return ticks_n_; }
		static uint32_t GetRenders() { return renders_n_; }

		static void reset()
		{
			ticks_n_ = 0;
			renders_n_ = 0;
		}

		static void AppTickCbB(trac::Event& e) { ticks_n_++; }
		static void AppTickCbNb(std::shared_ptr<trac::Event> e) { ticks_n_++; }

		static void AppRenderCbB(trac::Event& e) { renders_n_++; }
		static void AppRenderCbNb(std::shared_ptr<trac::Event> e) { renders_n_++; }
	};

	uint32_t EventDataStatic::ticks_n_ = 0;
	uint32_t EventDataStatic::renders_n_ = 0;

	/// @brief	Test the event dispatcher with class member functions as callbacks, with blocking events.
	GTEST_TEST(tractor, event_callback_member_blocking)
	{
		trac:: event_listener_remove_all();

		// Initial values should be zero
		EventData event_data;
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Create events
		trac::EventAppTick e_tick;
		trac::EventAppRendered e_rendered;

		// Add listener for tick event
		trac::listener_id_t listener_id_tick = trac::event_listener_add_b(
			trac::EventType::kAppTick, BIND_EVENT_FN(EventData::AppTickCbB, event_data)
		);
		
		// Dispatching events should call the listener
		trac::event_dispatch_b(e_tick);
		EXPECT_EQ(1, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		trac::event_dispatch_b(e_rendered);
		EXPECT_EQ(1, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Remove tick event listener and add listener for rendered event
		trac::event_listener_remove_b(listener_id_tick);
		trac::listener_id_t listener_id_rendered = trac::event_listener_add_b(
			trac::EventType::kAppRendered, BIND_EVENT_FN(EventData::AppRenderCbB, event_data)
		);

		// Dispatching events should call the listener
		trac::event_dispatch_b(e_tick);
		EXPECT_EQ(1, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		trac::event_dispatch_b(e_rendered);
		EXPECT_EQ(1, event_data.GetTicks());
		EXPECT_EQ(1, event_data.GetRenders());

		// Adding the tick listener back
		listener_id_tick = trac::event_listener_add_b(
			trac::EventType::kAppTick, BIND_EVENT_FN(EventData::AppTickCbB, event_data)
		);

		// Dispatching events should call both listeners
		trac::event_dispatch_b(e_tick);
		EXPECT_EQ(2, event_data.GetTicks());
		EXPECT_EQ(1, event_data.GetRenders());

		trac::event_dispatch_b(e_rendered);
		EXPECT_EQ(2, event_data.GetTicks());
		EXPECT_EQ(2, event_data.GetRenders());

		// Dispatching non-blocking events should not affect the event data
		// Create events
		std::shared_ptr<trac::EventAppTick> e_tick_nb = std::make_shared<trac::EventAppTick>();
		std::shared_ptr<trac::EventAppRendered> e_rendered_nb = std::make_shared<trac::EventAppRendered>();

		trac::event_dispatch_nb(e_tick_nb);
		EXPECT_EQ(2, event_data.GetTicks());
		EXPECT_EQ(2, event_data.GetRenders());

		trac::event_dispatch_nb(e_rendered_nb);
		EXPECT_EQ(2, event_data.GetTicks());
		EXPECT_EQ(2, event_data.GetRenders());

		// Removing all listeners and reseting the event data
		trac::event_listener_remove_all();
		event_data.reset();
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Dispatching events should do nothing without listeners
		trac::event_dispatch_b(e_tick);
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		trac::event_dispatch_b(e_rendered);
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Processing the event queue should not affect the event data
		trac::event_queue_process();
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Adding non-blocking listeners should not do anything when dispatching blocking events explicitly.
		trac::event_queue_clear();
		trac::event_listener_add_nb(
			trac::EventType::kAppTick, BIND_EVENT_FN(EventData::AppTickCbNb, event_data)
		);
		trac::event_listener_add_nb(
			trac::EventType::kAppRendered, BIND_EVENT_FN(EventData::AppRenderCbNb, event_data)
		);

		trac::event_dispatch_b(e_tick);
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		trac::event_dispatch_b(e_rendered);
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Processing the event queue should not affect the event data
		trac::event_queue_process();
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Removing all listeners and reseting the event data
		trac::event_listener_remove_all();
		event_data.reset();

		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		trac::event_queue_clear();
	}

	/// @brief	Test the event dispatcher with class member functions as callbacks, with non-blocking events.
	GTEST_TEST(tractor, event_callback_member_non_blocking)
	{
		trac::event_listener_remove_all();

		// Initial values should be zero
		EventData event_data;
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Create events
		std::shared_ptr<trac::EventAppTick> e_tick = std::make_shared<trac::EventAppTick>();
		std::shared_ptr<trac::EventAppRendered> e_rendered = std::make_shared<trac::EventAppRendered>();

		// Add listener for tick event
		trac::listener_id_t listener_id_tick = trac::event_listener_add_nb(
			trac::EventType::kAppTick, BIND_EVENT_FN(EventData::AppTickCbNb, event_data)
		);

		// Dispatching events should call the listener when processing the queue but not before.
		trac::event_dispatch_nb(e_tick);
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		trac::event_dispatch_nb(e_rendered);
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// The event queue should contain both events, but only the tick event should be processed.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(1, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Remove tick event listener and add listener for rendered event
		trac::event_listener_remove_nb(listener_id_tick);
		trac::listener_id_t listener_id_rendered = trac::event_listener_add_nb(
			trac::EventType::kAppRendered, BIND_EVENT_FN(EventData::AppRenderCbNb, event_data)
		);

		// Dispatching events should call the listener when processing the queue but not before.
		trac::event_dispatch_nb(e_tick);
		EXPECT_EQ(1, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		trac::event_dispatch_nb(e_rendered);
		EXPECT_EQ(1, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// The event queue should contain both events, but only the rendered event should be processed.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(1, event_data.GetTicks());
		EXPECT_EQ(1, event_data.GetRenders());

		// Adding the tick listener back
		listener_id_tick = trac::event_listener_add_nb(
			trac::EventType::kAppTick, BIND_EVENT_FN(EventData::AppTickCbNb, event_data)
		);

		// Dispatching events should call both listeners when processing the queue but not before.
		trac::event_dispatch_nb(e_tick);
		EXPECT_EQ(1, event_data.GetTicks());
		EXPECT_EQ(1, event_data.GetRenders());

		trac::event_dispatch_nb(e_rendered);
		EXPECT_EQ(1, event_data.GetTicks());
		EXPECT_EQ(1, event_data.GetRenders());

		// Dispatching the events but clearing the queue before processing should not affect the event data.
		trac::event_dispatch_nb(e_tick);
		trac::event_dispatch_nb(e_rendered);

		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_clear();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(1, event_data.GetTicks());
		EXPECT_EQ(1, event_data.GetRenders());

		EXPECT_TRUE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(1, event_data.GetTicks());
		EXPECT_EQ(1, event_data.GetRenders());

		// Clear the event data
		event_data.reset();
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Dispatching events should do nothing without listeners
		trac::event_listener_remove_all();
		trac::event_dispatch_nb(e_tick);
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		trac::event_dispatch_nb(e_rendered);
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		trac::event_queue_process();
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Adding blocking listeners should not do anything when dispatching non-blocking events explicitly.
		trac::event_listener_add_b(
			trac::EventType::kAppTick, BIND_EVENT_FN(EventData::AppTickCbB, event_data)
		);
		trac::event_listener_add_b(
			trac::EventType::kAppRendered, BIND_EVENT_FN(EventData::AppRenderCbB, event_data)
		);

		trac::event_dispatch_nb(e_tick);
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		trac::event_dispatch_nb(e_rendered);
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Processing the event queue should not affect the event data
		trac::event_queue_process();
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		// Removing all listeners and reseting the event data
		trac::event_listener_remove_all();
		event_data.reset();
		EXPECT_EQ(0, event_data.GetTicks());
		EXPECT_EQ(0, event_data.GetRenders());

		trac::event_queue_clear();
	}


	/**
	 * @brief	Tests the event dispatcher with blocking events. This will test that the following functions work as expected:
	 * 			- trac::event_dispatch_b
	 * 			- trac::event_listener_add_b
	 * 			- trac::event_listener_remove_b
	 * 			And that the explicit blocking functions and events do not affect the event queue.
	 */
	GTEST_TEST(tractor, event_blocking)
	{
		trac::event_listener_remove_all();

		// Initial values should be zero
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Create events
		trac::EventAppTick e_tick;
		trac::EventAppRendered e_rendered;

		// Dispatching blocking events should do nothing without listeners
		trac::event_dispatch_b(e_tick);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch_b(e_rendered);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Dispatching blocking events should not affect the non-blocking event queue
		EXPECT_TRUE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Add listener for tick event
		trac::listener_id_t listener_id_tick = trac::event_listener_add_b(trac::EventType::kAppTick, EventDataStatic::AppTickCbB);

		// Dispatching blocking events should call the listener
		trac::event_dispatch_b(e_tick);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch_b(e_rendered);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Dispatching blocking events should not affect the event queue
		EXPECT_TRUE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Remove tick event listener and add listener for rendered event
		trac::event_listener_remove_b(listener_id_tick);
		trac::listener_id_t listener_id_rendered = trac::event_listener_add_b(trac::EventType::kAppRendered, EventDataStatic::AppRenderCbB);

		// Dispatching blocking events should call the listener
		trac::event_dispatch_b(e_tick);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch_b(e_rendered);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		// Dispatching blocking events should not affect the event queue
		EXPECT_TRUE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		// Adding the tick listener back
		listener_id_tick = trac::event_listener_add_b(trac::EventType::kAppTick, EventDataStatic::AppTickCbB);

		// Dispatching blocking events should call both listeners
		trac::event_dispatch_b(e_tick);
		EXPECT_EQ(2, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		trac::event_dispatch_b(e_rendered);
		EXPECT_EQ(2, EventDataStatic::GetTicks());
		EXPECT_EQ(2, EventDataStatic::GetRenders());

		// Removing all blocking listeners and reseting the event data
		trac::event_listener_remove_all_b();
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Dispatching blocking events should do nothing without listeners
		trac::event_dispatch_b(e_tick);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch_b(e_rendered);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Adding non-blocking listeners should not do anything when dispatching blocking events explicitly.
		trac::event_listener_add_nb(trac::EventType::kAppTick, EventDataStatic::AppTickCbNb);
		trac::event_listener_add_nb(trac::EventType::kAppRendered, EventDataStatic::AppRenderCbNb);

		trac::event_dispatch_b(e_tick);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch_b(e_rendered);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Dispatching blocking events should not affect the event queue even if there are non-blocking listeners.
		EXPECT_TRUE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Removing all listeners and reseting the event data
		trac::event_listener_remove_all();
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());
	}

	/**
	 * @brief	Tests the event dispatcher with non-blocking events. This will test that the following functions work as expected:
	 * 			- trac::event_dispatch_nb
	 * 			- trac::event_listener_add_nb
	 * 			- trac::event_listener_remove_nb
	 * 			- trac::event_queue_process
	 * 			- trac::event_queue_process_one
	 * 			- trac::event_queue_clear
	 * 			- trac::event_queue_empty
	 * 			And that the explicit non-blocking functions and events do not trigger blocking events.
	 */
	GTEST_TEST(tractor, event_non_blocking)
	{
		trac::event_listener_remove_all();

		// Initial values should be zero
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Create events
		std::shared_ptr<trac::Event> e_tick = std::make_shared<trac::EventAppTick>();
		std::shared_ptr<trac::Event> e_rendered = std::make_shared<trac::EventAppRendered>();

		// Dispatching non-blocking events should do nothing without listeners
		trac::event_dispatch_nb(e_tick);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch_nb(e_rendered);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// The event queue should contain the events, but no callbacks should be called. Therefore, processing the queue should not affect the event data.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Add listener for tick event
		trac::listener_id_t listener_id_tick = trac::event_listener_add_nb(trac::EventType::kAppTick, EventDataStatic::AppTickCbNb);

		// Dispatching non-blocking events should call the listener when processing the queue but not before.
		trac::event_dispatch_nb(e_tick);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch_nb(e_rendered);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// The event queue should contain both events, but only the tick event should be processed.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Remove tick event listener and add listener for rendered event
		trac::event_listener_remove_nb(listener_id_tick);
		trac::listener_id_t listener_id_rendered = trac::event_listener_add_nb(trac::EventType::kAppRendered, EventDataStatic::AppRenderCbNb);

		// Dispatching non-blocking events should call the listener when processing the queue but not before.
		trac::event_dispatch_nb(e_tick);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch_nb(e_rendered);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// The event queue should contain both events, but only the rendered event should be processed.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		// Adding the tick listener back
		listener_id_tick = trac::event_listener_add_nb(trac::EventType::kAppTick, EventDataStatic::AppTickCbNb);

		// Dispatching non-blocking events should call both listeners when processing the queue but not before.
		trac::event_dispatch_nb(e_tick);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		trac::event_dispatch_nb(e_rendered);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		// The event queue should contain both events, and both should be processed.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(2, EventDataStatic::GetTicks());
		EXPECT_EQ(2, EventDataStatic::GetRenders());

		// Dispatching the events but clearing the queue before processing should not affect the event data.
		trac::event_dispatch_nb(e_tick);
		trac::event_dispatch_nb(e_rendered);

		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_clear();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(2, EventDataStatic::GetTicks());
		EXPECT_EQ(2, EventDataStatic::GetRenders());

		EXPECT_TRUE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(2, EventDataStatic::GetTicks());
		EXPECT_EQ(2, EventDataStatic::GetRenders());

		// Clear the event data
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Events should be queued in the order they are dispatched when processed individually.
		trac::event_dispatch_nb(e_tick);
		trac::event_dispatch_nb(e_rendered);
		trac::event_dispatch_nb(e_tick);
		trac::event_dispatch_nb(e_tick);
		trac::event_dispatch_nb(e_rendered);

		EXPECT_FALSE(trac::event_queue_empty());
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process_one();
		EXPECT_FALSE(trac::event_queue_empty());
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process_one();
		EXPECT_FALSE(trac::event_queue_empty());
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process_one();
		EXPECT_FALSE(trac::event_queue_empty());
		EXPECT_EQ(2, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process_one();
		EXPECT_FALSE(trac::event_queue_empty());
		EXPECT_EQ(3, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process_one();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(3, EventDataStatic::GetTicks());
		EXPECT_EQ(2, EventDataStatic::GetRenders());

		// Removing all non-blocking listeners and reseting the event data
		trac::event_listener_remove_all_nb();
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Dispatching non-blocking events should do nothing without listeners
		trac::event_dispatch_nb(e_tick);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch_nb(e_rendered);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Adding blocking listeners should not do anything when dispatching non-blocking events explicitly.
		trac::event_listener_add_b(trac::EventType::kAppTick, EventDataStatic::AppTickCbB);
		trac::event_listener_add_b(trac::EventType::kAppRendered, EventDataStatic::AppRenderCbB);

		trac::event_dispatch_nb(e_tick);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch_nb(e_rendered);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Removing all listeners and reseting the event data
		trac::event_listener_remove_all();
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());
	}

	/**
	 * @brief	Tests the event dispatcher with generic events. This will test that 'event_dispatch' dispatches events in a blocking manner when blocking
	 * 			listeners are added and simultaneously dispatches non-blocking events when non-blocking listeners are added.
	 */
	GTEST_TEST(tractor, event_generic)
	{
		trac::event_listener_remove_all();

		// Initial values should be zero
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Create events
		std::shared_ptr<trac::Event> e_tick = std::make_shared<trac::EventAppTick>();
		std::shared_ptr<trac::Event> e_rendered = std::make_shared<trac::EventAppRendered>();

		// Dispatching events should do nothing without listeners
		trac::event_dispatch(e_tick);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch(e_rendered);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// The event queue should contain the events, but no callbacks should be called. Therefore, processing the queue should not affect the event data.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Add blocking listener for tick event
		trac::listener_id_t listener_b_id_tick = trac::event_listener_add_b(trac::EventType::kAppTick, EventDataStatic::AppTickCbB);

		// Dispatching events should call the blocking listener immediately.
		trac::event_dispatch(e_tick);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch(e_rendered);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// The event queue should contain both events, and neither should be processed.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Reset the event data
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Add blocking listener for rendered event
		trac::listener_id_t listener_b_id_rendered = trac::event_listener_add_b(trac::EventType::kAppRendered, EventDataStatic::AppRenderCbB);

		// Dispatching events should call both blocking listeners immediately.
		trac::event_dispatch(e_tick);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch(e_rendered);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		// The event queue should contain both events, and neither should be processed.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		// Reset the event data
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Add non-blocking listener for tick event
		trac::listener_id_t listener_nb_id_tick = trac::event_listener_add_nb(trac::EventType::kAppTick, EventDataStatic::AppTickCbNb);

		// Dispatching events should immidiately call the blocking listener, and the non-blocking tick event should be processed when the queue is processed.
		trac::event_dispatch(e_tick);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch(e_rendered);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		// The event queue should contain both events, and the tick event should be processed.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(2, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		// Reset the event data
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Add non-blocking listener for rendered event
		trac::listener_id_t listener_nb_id_rendered = trac::event_listener_add_nb(trac::EventType::kAppRendered, EventDataStatic::AppRenderCbNb);

		// Dispatching events should immidiately call the blocking listener, and the non-blocking tick event should be processed when the queue is processed.
		trac::event_dispatch(e_tick);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch(e_rendered);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		// The event queue should contain both events, and both should be processed.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(2, EventDataStatic::GetTicks());
		EXPECT_EQ(2, EventDataStatic::GetRenders());

		// Removing the blocking event listeners
		trac::event_listener_remove_all_b();

		// Reset the event data
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Dispatching events should only apply to the non-blocking listeners
		trac::event_dispatch(e_tick);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch(e_rendered);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// The event queue should contain both events, and both should be processed.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		// Removing the non-blocking event listeners
		trac::event_listener_remove_all_nb();

		// Reset the event data
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Dispatching events should do nothing without listeners
		trac::event_dispatch(e_tick);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch(e_rendered);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// The event queue should contain both events, but no callbacks should be called. Therefore, the event data should be zero.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());
		
		// Re-add all event listeners and remove all to ensure that 'event_listener_remove_all' works as expected.
		trac::event_listener_add_b(trac::EventType::kAppTick, EventDataStatic::AppTickCbB);
		trac::event_listener_add_b(trac::EventType::kAppRendered, EventDataStatic::AppRenderCbB);
		trac::event_listener_add_nb(trac::EventType::kAppTick, EventDataStatic::AppTickCbNb);
		trac::event_listener_add_nb(trac::EventType::kAppRendered, EventDataStatic::AppRenderCbNb);

		// Dispatching events should call all listeners
		trac::event_dispatch(e_tick);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch(e_rendered);
		EXPECT_EQ(1, EventDataStatic::GetTicks());
		EXPECT_EQ(1, EventDataStatic::GetRenders());

		// The event queue should contain both events, and both should be processed.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(2, EventDataStatic::GetTicks());
		EXPECT_EQ(2, EventDataStatic::GetRenders());

		// Removing all event listeners
		trac::event_listener_remove_all();

		// Reset the event data
		EventDataStatic::reset();
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// Dispatching events should do nothing without listeners
		trac::event_dispatch(e_tick);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		trac::event_dispatch(e_rendered);
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());

		// The event queue should contain both events, but no callbacks should be called. Therefore, the event data should be zero.
		EXPECT_FALSE(trac::event_queue_empty());
		trac::event_queue_process();
		EXPECT_TRUE(trac::event_queue_empty());
		EXPECT_EQ(0, EventDataStatic::GetTicks());
		EXPECT_EQ(0, EventDataStatic::GetRenders());
	}

	/// @brief Test that the insertion operator works as expected.
	GTEST_TEST(tractor, event_insertion)
	{
		// Create tick event
		trac::EventAppTick e_tick;

		// Inserting the events into a stream should not cause any errors
		std::stringstream ss_tick;
		ss_tick << e_tick;

		// The stream should contain the event name
		EXPECT_STREQ("EventAppTick", ss_tick.str().c_str());

		// Create rendered event
		trac::EventAppRendered e_rendered;

		// Inserting the events into a stream should not cause any errors
		std::stringstream ss_rendered;
		ss_rendered << e_rendered;

		// The stream should contain the event name
		EXPECT_STREQ("EventAppRendered", ss_rendered.str().c_str());

		// The same should be true for events with pointer type
		std::shared_ptr<trac::Event> e_tick_ptr = std::make_shared<trac::EventAppTick>();
		std::stringstream ss_tick_ptr;
		ss_tick_ptr << e_tick_ptr;
		EXPECT_STREQ("EventAppTick", ss_tick_ptr.str().c_str());

		std::shared_ptr<trac::Event> e_rendered_ptr = std::make_shared<trac::EventAppRendered>();
		std::stringstream ss_rendered_ptr;
		ss_rendered_ptr << e_rendered_ptr;
		EXPECT_STREQ("EventAppRendered", ss_rendered_ptr.str().c_str());
	}

	class EventDetailedData
	{
	private:
		static uint32_t cb_count_;
		static std::string name_;
		static trac::EventType type_;
		static trac::event_category_t categories_;
		static trac::timestamp_t timestamp_;
		static std::string string_representation_;
		static std::shared_ptr<trac::Event> event_;

		EventDetailedData(){}

	public:

		static void Reset()
		{
			cb_count_ = 0;
			name_ = "";
			type_ = trac::EventType::kNone;
			categories_ = trac::EventCategory::kNone;
			timestamp_ = 0;
			string_representation_ = "";
			event_ = nullptr;
		}

		static void SetData(const std::shared_ptr<trac::Event> e)
		{
			cb_count_++;
			name_ = e->GetName();
			type_ = e->GetType();
			categories_ = e->GetCategoryFlags();
			timestamp_ = e->GetTimestampMs();
			string_representation_ = e->ToString();
			event_ = e;
		}

		static uint32_t GetCbCount() { return cb_count_; }
		static std::string GetName() { return name_; }
		static trac::EventType GetType() { return type_; }
		static trac::event_category_t GetCategories() { return categories_; }
		static trac::timestamp_t GetTimestamp() { return timestamp_; }
		static std::string GetStringRepresentation() { return string_representation_; }
		static std::shared_ptr<trac::Event> GetEvent() { return event_; }

		static void cb(std::shared_ptr<trac::Event> e){ SetData(e); }
	};

	uint32_t EventDetailedData::cb_count_ = 0;
	std::string EventDetailedData::name_ = "";
	trac::EventType EventDetailedData::type_ = trac::EventType::kNone;
	trac::event_category_t EventDetailedData::categories_ = trac::EventCategory::kNone;
	trac::timestamp_t EventDetailedData::timestamp_ = 0;
	std::string EventDetailedData::string_representation_ = "";
	std::shared_ptr<trac::Event> EventDetailedData::event_ = nullptr;

	
	/// @brief	Tests the event dispatcher with detailed events. This will test that calling the members of the event base class works as expected.
	GTEST_TEST(tractor, event_base_class)
	{
		trac::event_listener_remove_all();

		// Create tick event as a simple example event.
		std::shared_ptr<trac::Event> e = std::make_shared<trac::EventAppRendered>();
		const uint32_t e_timestamp = e->GetTimestampMs();

		// Test functions directly without going through the dispatcher.
		EXPECT_STREQ("EventAppRendered", e->GetName());
		EXPECT_EQ(trac::EventType::kAppRendered, e->GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kDisplay), e->GetCategoryFlags());
		EXPECT_EQ(e_timestamp, e->GetTimestampMs());
		EXPECT_STREQ("EventAppRendered", e->ToString().c_str());

		// The event should only be in the application and display categories.
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kNone)		);
		EXPECT_TRUE(	e->IsInCategory(trac::EventCategory::kApplication)	);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kInput)		);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kDevice)		);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kWindow)		);
		EXPECT_TRUE(	e->IsInCategory(trac::EventCategory::kDisplay)		);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kAudio)		);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kKeyboard)	);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kMouse)		);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kController)	);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kJoystick)	);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kButton)		);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kAxis)		);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kTouch)		);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kHat)			);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kBall)		);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kSensor)		);
		EXPECT_FALSE(	e->IsInCategory(trac::EventCategory::kEngineFinal)	);

		// Initial values of EventDetailedData should be zero/blank before dispatching.
		EventDetailedData::Reset();
		EXPECT_EQ(0, EventDetailedData::GetCbCount());
		EXPECT_STREQ("", EventDetailedData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, EventDetailedData::GetType());
		EXPECT_EQ(trac::EventCategory::kNone, EventDetailedData::GetCategories());
		EXPECT_EQ(0, EventDetailedData::GetTimestamp());
		EXPECT_STREQ("", EventDetailedData::GetStringRepresentation().c_str());
		EXPECT_EQ(nullptr, EventDetailedData::GetEvent());

		// Dispatching events should do nothing without listeners
		trac::event_dispatch(e);
		trac::event_queue_process();

		EXPECT_EQ(0, EventDetailedData::GetCbCount());
		EXPECT_STREQ("", EventDetailedData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kNone, EventDetailedData::GetType());
		EXPECT_EQ(trac::EventCategory::kNone, EventDetailedData::GetCategories());
		EXPECT_EQ(0, EventDetailedData::GetTimestamp());
		EXPECT_STREQ("", EventDetailedData::GetStringRepresentation().c_str());
		EXPECT_EQ(nullptr, EventDetailedData::GetEvent());		

		// Add listener for tick event
		trac::listener_id_t listener_id_tick = trac::event_listener_add_nb(trac::EventType::kAppRendered, EventDetailedData::cb);

		// Dispatching events and processing the queue should now update the values.
		trac::event_dispatch(e);
		trac::event_queue_process();

		EXPECT_EQ(1, EventDetailedData::GetCbCount());
		EXPECT_STREQ("EventAppRendered", EventDetailedData::GetName().c_str());
		EXPECT_EQ(trac::EventType::kAppRendered, EventDetailedData::GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kDisplay), EventDetailedData::GetCategories());
		EXPECT_EQ(e_timestamp, EventDetailedData::GetTimestamp());
		EXPECT_STREQ("EventAppRendered", EventDetailedData::GetStringRepresentation().c_str());
		EXPECT_EQ(e, EventDetailedData::GetEvent());

		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kNone)			);
		EXPECT_TRUE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kApplication)	);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kInput)		);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kDevice)		);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kWindow)		);
		EXPECT_TRUE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kDisplay)		);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kAudio)		);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kKeyboard)		);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kMouse)		);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kController)	);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kJoystick)		);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kButton)		);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kAxis)			);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kTouch)		);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kHat)			);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kBall)			);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kSensor)		);
		EXPECT_FALSE(	EventDetailedData::GetEvent()->IsInCategory(trac::EventCategory::kEngineFinal)	);
	}

	/// @brief	Tests event constructors and assignment operators.
	GTEST_TEST(tractor, event_construct_and_assign)
	{
		// Test constructor
		const trac::EventAppRendered e;
		const uint32_t e_timestamp = e.GetTimestampMs();

		// Check that the original has the expected values
		EXPECT_STREQ("EventAppRendered", e.GetName());
		EXPECT_EQ(trac::EventType::kAppRendered, e.GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kDisplay), e.GetCategoryFlags());
		EXPECT_EQ(e_timestamp, e.GetTimestampMs());
		EXPECT_STREQ("EventAppRendered", e.ToString().c_str());
		
		// Test copy constructor
		trac::EventAppRendered e_copy(e);

		// Check that the copy has the expected values
		EXPECT_STREQ("EventAppRendered", e_copy.GetName());
		EXPECT_EQ(trac::EventType::kAppRendered, e_copy.GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kDisplay), e_copy.GetCategoryFlags());
		EXPECT_EQ(e_timestamp, e_copy.GetTimestampMs());
		EXPECT_STREQ("EventAppRendered", e_copy.ToString().c_str());

		// Check that the two copies are equal
		EXPECT_STREQ(e.GetName(), e_copy.GetName());
		EXPECT_EQ(e.GetType(), e_copy.GetType());
		EXPECT_EQ(e.GetCategoryFlags(), e_copy.GetCategoryFlags());
		EXPECT_EQ(e.GetTimestampMs(), e_copy.GetTimestampMs());
		EXPECT_EQ(e.ToString(), e_copy.ToString());

		// Test copy assignment operator		
		trac::EventAppRendered e_copy_assigned = e;

		// Check that the copy has the expected values
		EXPECT_STREQ("EventAppRendered", e_copy_assigned.GetName());
		EXPECT_EQ(trac::EventType::kAppRendered, e_copy_assigned.GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kDisplay), e_copy_assigned.GetCategoryFlags());
		EXPECT_EQ(e_timestamp, e_copy_assigned.GetTimestampMs());
		EXPECT_STREQ("EventAppRendered", e_copy_assigned.ToString().c_str());

		// Check that the two copies are equal
		EXPECT_STREQ(e.GetName(), e_copy_assigned.GetName());
		EXPECT_EQ(e.GetType(), e_copy_assigned.GetType());
		EXPECT_EQ(e.GetCategoryFlags(), e_copy_assigned.GetCategoryFlags());
		EXPECT_EQ(e.GetTimestampMs(), e_copy_assigned.GetTimestampMs());
		EXPECT_EQ(e.ToString(), e_copy_assigned.ToString());

		// Test move constructor
		trac::EventAppRendered e_move(std::move(e_copy));

		// Check that the moved object has the expected values
		EXPECT_STREQ("EventAppRendered", e_move.GetName());
		EXPECT_EQ(trac::EventType::kAppRendered, e_move.GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kDisplay), e_move.GetCategoryFlags());
		EXPECT_EQ(e_timestamp, e_move.GetTimestampMs());
		EXPECT_STREQ("EventAppRendered", e_move.ToString().c_str());

		// Check that the original object has the expected values
		EXPECT_STREQ("EventAppRendered", e_copy.GetName());
		EXPECT_EQ(trac::EventType::kAppRendered, e_copy.GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kDisplay), e_copy.GetCategoryFlags());
		EXPECT_EQ(e_timestamp, e_copy.GetTimestampMs());
		EXPECT_STREQ("EventAppRendered", e_copy.ToString().c_str());

		// Test move assignment operator
		trac::EventAppRendered e_move_assigned = std::move(e_copy_assigned);

		// Check that the moved object has the expected values
		EXPECT_STREQ("EventAppRendered", e_move_assigned.GetName());
		EXPECT_EQ(trac::EventType::kAppRendered, e_move_assigned.GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kDisplay), e_move_assigned.GetCategoryFlags());
		EXPECT_EQ(e_timestamp, e_move_assigned.GetTimestampMs());
		EXPECT_STREQ("EventAppRendered", e_move_assigned.ToString().c_str());

		// Check that the original object has the expected values
		EXPECT_STREQ("EventAppRendered", e_copy_assigned.GetName());
		EXPECT_EQ(trac::EventType::kAppRendered, e_copy_assigned.GetType());
		EXPECT_EQ((trac::EventCategory::kApplication | trac::EventCategory::kDisplay), e_copy_assigned.GetCategoryFlags());
		EXPECT_EQ(e_timestamp, e_copy_assigned.GetTimestampMs());
		EXPECT_STREQ("EventAppRendered", e_copy_assigned.ToString().c_str());
	}

	class TestEvent : public trac::Event
	{
	private:
		static uint32_t construct_count_;
		static uint32_t destruct_count_;

	public:

		TestEvent(){construct_count_++;}
		~TestEvent(){destruct_count_++;}

		static void Reset()
		{
			construct_count_ = 0;
			destruct_count_ = 0;
		}

		virtual const char* GetName() const override {return "TestEvent";}
		virtual trac::EventType GetType() const override {return trac::EventType::kNone;}
		virtual trac::event_category_t GetCategoryFlags() const override {return trac::EventCategory::kNone;}
		virtual trac::timestamp_t GetTimestampMs() const override {return 0;}
		virtual std::string ToString() const override {return "TestEvent";}

		static uint32_t GetConstructCount(){return construct_count_;}
		static uint32_t GetDestructCount(){return destruct_count_;}
	};

	uint32_t TestEvent::construct_count_ = 0;
	uint32_t TestEvent::destruct_count_ = 0;
	
	/**
	 * @brief	Test event class polymorphism. It is expected that pointers to both the derived and base class can be used interchangeably. And that deletion
	 * 			of either the derived or base class will call the destructor of both and free allocated memory.
	 */
	GTEST_TEST(tractor, event_polymorphism)
	{
		// Initial values should be zero
		EXPECT_EQ(0, TestEvent::GetConstructCount());
		EXPECT_EQ(0, TestEvent::GetDestructCount());

		// Create event using a pointer to the base class
		std::shared_ptr<trac::Event> e = std::make_shared<TestEvent>();

		// One object should have been constructed, none destroyed.
		EXPECT_EQ(1, TestEvent::GetConstructCount());
		EXPECT_EQ(0, TestEvent::GetDestructCount());

		// Create event using a pointer to the derived class
		std::shared_ptr<TestEvent> e_derived = std::make_shared<TestEvent>();

		// Two objects should have been constructed, none destroyed.
		EXPECT_EQ(2, TestEvent::GetConstructCount());
		EXPECT_EQ(0, TestEvent::GetDestructCount());

		// Delete the base class. This should call the destructor of both the base and derived class (we can only see the derived).
		e = nullptr;

		// Two objects should have been constructed, one destroyed.
		EXPECT_EQ(2, TestEvent::GetConstructCount());
		EXPECT_EQ(1, TestEvent::GetDestructCount());

		// Delete the derived class
		e_derived = nullptr;

		// Two objects should have been constructed, two destroyed.
		EXPECT_EQ(2, TestEvent::GetConstructCount());
		EXPECT_EQ(2, TestEvent::GetDestructCount());

		// Test the same with a raw pointer
		TestEvent::Reset();

		// Initial values should be zero
		EXPECT_EQ(0, TestEvent::GetConstructCount());
		EXPECT_EQ(0, TestEvent::GetDestructCount());

		// Create event using a pointer to the base class
		trac::Event* e_raw = new TestEvent();

		// One object should have been constructed, none destroyed.
		EXPECT_EQ(1, TestEvent::GetConstructCount());
		EXPECT_EQ(0, TestEvent::GetDestructCount());

		// Create event using a pointer to the derived class
		TestEvent* e_derived_raw = new TestEvent();

		// Two objects should have been constructed, none destroyed.
		EXPECT_EQ(2, TestEvent::GetConstructCount());
		EXPECT_EQ(0, TestEvent::GetDestructCount());

		// Delete the base class. This should call the destructor of both the base and derived class (we can only see the derived).
		delete e_raw;

		// Two objects should have been constructed, one destroyed.
		EXPECT_EQ(2, TestEvent::GetConstructCount());
		EXPECT_EQ(1, TestEvent::GetDestructCount());

		// Delete the derived class
		delete e_derived_raw;

		// Two objects should have been constructed, two destroyed.
		EXPECT_EQ(2, TestEvent::GetConstructCount());
		EXPECT_EQ(2, TestEvent::GetDestructCount());
	}

} // namespace test