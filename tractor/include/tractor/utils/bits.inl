/**
 * @file	bits.inl
 * @brief	Inlined file containing inline bit manipulation functions. This file should not be included directly,
 * 			but through 'bits.hpp'.
 * 
 * @author	Erlend Elias Isachsen
 * @date	2024-08-11
 * */

#ifndef BITS_HPP_
#error "Do not include this file directly. Include logger.hpp instead, through which this file is included indirectly."
#endif // BITS_HPP_

namespace trac
{
	/**
	 * @brief	Check if a bit is set in a value.
	 * 
	 * @param value	The value to check.
	 * @param bit	The bit to check.
	 * @return bool	True if the bit is set, false otherwise.
	 */
	bool is_bit_set(const uint32_t value, const uint32_t bit)
	{
		return (value & (1 << bit)) != 0;
	}

	/**
	 * @brief	Set a bit in a value to either 0 or 1.
	 * 
	 * @param value	The value to set the bit in.
	 * @param bit	The bit/position to set.
	 * @param set	True to set the bit to 1, false to set it to 0.
	 */
	void bit_set_to(uint32_t& value, const uint32_t bit, const bool set)
	{
		value = value & ~(1 << bit) | (set << bit);
	}

	/**
	 * @brief	Set a bit at a given position in a value to 1.
	 * 
	 * @param value	The value to set the bit in.
	 * @param bit	The bit/position to set.
	 */
	void bit_set(uint32_t& value, const uint32_t bit)
	{
		value |= (1 << bit);
	}

	/**
	 * @brief	Clear a bit at a given position in a value (set to 0).
	 * 
	 * @param value	The value to clear the bit in.
	 * @param bit	The bit/position to clear.
	 */
	void bit_clear(uint32_t& value, const uint32_t bit)
	{
		value &= ~(1 << bit);
	}

	/**
	 * @brief	Toggle a bit at a given position in a value.
	 * 
	 * @param value	The value to toggle the bit in.
	 * @param bit	The bit/position to toggle.
	 */
	void bit_toggle(uint32_t& value, const uint32_t bit)
	{
		value ^= (1 << bit);
	}



} // namespace trac


#ifndef BITS_INL_
#define BITS_INL_

#endif /* BITS_INL_ */