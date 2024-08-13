/**
 * @file	utils.inl
 * @brief	Inlined file containing inline utility functions. This file should not be included directly,
 * 			but through 'utils.hpp'.
 * 
 * @author	Erlend Elias Isachsen
 * @date	2024-08-13
 */


#ifndef UTILS_HPP_
#error "Do not include this file directly. Include utils.hpp instead, through which this file is included indirectly."
#endif // UTILS_HPP_

#ifndef UTILS_INL_
/// @brief Header guard.
#define UTILS_INL_

#include "bits.hpp"

namespace trac
{
	/**
	 * @brief	Clamp a signed integer to a positive value. If the integer is negative, it will be clamped to 0, otherwise it will be returned as is.
	 * 
	 * @tparam INT_T	The type of the integer to clamp.
	 * @param signed_int	The signed integer to clamp.
	 * @return INT_T	The clamped integer.
	 * @retval 0	If the signed integer is negative.
	 */
	template <typename INT_T>
	INT_T clamp_int_to_positive(const INT_T signed_int)
	{
		return signed_int & ~(signed_int >> (sizeof(INT_T) * 8 - 1));
	}

	/**
	 * @brief	Clamp a signed integer to a positive value. If the integer is negative, it will be clamped to 0, otherwise it will be returned as is.
	 * 			The integer is passed by reference and will be modified directly.
	 * 
	 * @tparam INT_T	The type of the integer to clamp.
	 * @param signed_int	The signed integer to clamp.
	 */
	template <typename INT_T>
	void clamp_int_to_positive_ref(INT_T &signed_int)
	{
		signed_int = signed_int & ~(signed_int >> (sizeof(INT_T) * 8 - 1));
	}

	/**
	 * @brief	Clamp a signed integer to a negative value. If the integer is positive, it will be clamped to 0, otherwise it will be returned as is.
	 * 
	 * @tparam INT_T	The type of the integer to clamp.
	 * @param signed_int	The signed integer to clamp.
	 * @return INT_T	The clamped integer.
	 * @retval 0	If the signed integer is positive.
	 */
	template <typename INT_T>
	INT_T clamp_int_to_negative(const INT_T signed_int)
	{
		return signed_int & (signed_int >> (sizeof(INT_T) * 8 - 1));
	}

	/**
	 * @brief	Clamp a signed integer to a negative value. If the integer is positive, it will be clamped to 0, otherwise it will be returned as is.
	 * 			The integer is passed by reference and will be modified directly.
	 * 
	 * @tparam INT_T	The type of the integer to clamp.
	 * @param signed_int	The signed integer to clamp.
	 */
	template <typename INT_T>
	void clamp_int_to_negative_ref(INT_T &signed_int)
	{
		signed_int = signed_int & (signed_int >> (sizeof(INT_T) * 8 - 1));
	}

	/**
	 * @brief	Clamps an unsigned integer to the max value of the signed integer of the equal size or smaller. Avoids unsigned int overflowing to
	 * 			negative values when cast to a signed integer.
	 * 
	 * @tparam INT_T	The type of the signed integer to clamp to (same size as UINT_T or smaller).
	 * @tparam UINT_T	The type of the unsigned integer to clamp.
	 * @param unsigned_int	The unsigned integer to clamp.
	 * @return INT_T	The clamped integer.
	 */
	template <typename INT_T, typename UINT_T>
	inline INT_T clamp_uint_to_int(UINT_T unsigned_int)
	{
		static_assert(
			sizeof(INT_T) <= sizeof(UINT_T),
			"The signed integer type must be smaller or equal in size to the unsigned integer type. When larger, use direct casting."
		);

		return (downshift_mask<INT_T>(unsigned_int)) ? signed_max<INT_T>() : unsigned_int;
	}

	/**
	 * @brief	Clamps an unsigned integer to the max value of the signed integer of equal number of bits. Avoids unsigned int overflowing to negative values
	 * 			when cast to a signed integer. The unsigned integer is passed by reference and will be modified directly.
	 * 
	 * @tparam INT_T	The type of the signed integer to clamp to (same size as UINT_T, for instance: int32_t for uint32_t).
	 * @tparam UINT_T	The type of the unsigned integer to clamp (same size as INT_T, for instance: uint32_t for int32_t).
	 * @param unsigned_int	The unsigned integer to clamp, passed by reference.
	 */
	template <typename INT_T, typename UINT_T>
	inline void clamp_uint_to_int_ref(UINT_T &unsigned_int)
	{
		static_assert(
			sizeof(INT_T) <= sizeof(UINT_T),
			"The signed integer type must be smaller or equal in size to the unsigned integer type. When larger, use direct casting."
		);
		unsigned_int = (downshift_mask<INT_T>(unsigned_int)) ? signed_max<INT_T>() : unsigned_int;
	}
}

#endif /* UTILS_INL_
 */