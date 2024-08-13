/**
 * @file	bits.hpp
 * @brief	File containing bit manipulation functions and macros.
 * 
 * @author	Erlend Elias Isachsen
 * @date	2024-08-11
 */

#ifndef BITS_HPP_
#define BITS_HPP_

#include <stdint.h>

namespace trac
{
	/**
	 * @brief	Generates a bit mask with a single bit set at the specified position.
	 * 
	 * @param x The position of the bit to set.
	 */
	#define BIT(x) (1 << x)

	inline bool is_bit_set(uint32_t value, uint32_t bit);
	inline void bit_set_to(uint32_t& value, uint32_t bit, bool set);
	inline void bit_set(uint32_t& value, uint32_t bit);
	inline void bit_clear(uint32_t& value, uint32_t bit);
	inline void bit_toggle(uint32_t& value, uint32_t bit);

	template <typename INT_T>
	inline INT_T signed_max();

	template <typename INT_T, typename UINT_T>
	inline UINT_T downshift_mask(UINT_T value);
	

} // namespace trac


#include "bits.inl"

#endif /* BITS_HPP_ */