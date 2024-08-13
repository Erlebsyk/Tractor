/**
 * @file	bits.inl
 * @brief	Inlined file containing inline bit manipulation functions. This file should not be included directly,
 * 			but through 'bits.hpp'.
 * 
 * @author	Erlend Elias Isachsen
 * @date	2024-08-11
 * */

#ifndef BITS_HPP_
#error "Do not include this file directly. Include bits.hpp instead, through which this file is included indirectly."
#endif // BITS_HPP_

#ifndef BITS_INL_
/// @brief Header guard.
#define BITS_INL_

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

	/**
	 * @brief	Returns the (positive) maximum signed of provided (signed) type.
	 * 
	 * @tparam INT The signed type to get the max value of (for example int32_t).
	 */
	template <typename INT_T>
	INT_T signed_max()
	{
		return (INT_T)(((INT_T)(-1) << (sizeof(INT_T) * 8 - 1))-1);
	}

	/**
	 * @brief	Removed all bits from the 'value' that are "invisible" to a signed integer of type INT_T. If they are the same size, this is the MSB.
	 * 			If the signed integer is smaller, it is all the bits from the signed MSB and up.
	 * 
	 * @tparam INT_T	The signed integer type to bitshift for (i.e. number of bytes to shift).
	 * @tparam UINT_T	The unsigned integer type to modify.
	 * @param value	The variable to modify with the bitshift.
	 */
	template <typename INT_T, typename UINT_T>
	UINT_T downshift_mask(UINT_T value)
	{
		static_assert(
			sizeof(INT_T) <= sizeof(UINT_T),
			"The signed integer type must be smaller or equal in size to the unsigned integer type to safely downshift the mask."
		);
		return value >> (sizeof(INT_T) * 8 - 1);
	}

} // namespace trac

#endif /* BITS_INL_ */