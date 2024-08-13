/**
 * @file	utils.hpp
 * @brief	Holds utility functions and classes for the tractor game engine library.
 * 
 * @author	Erlend Elias Isachsen
 * @date	2024-08-13
 * */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <stdint.h>

namespace trac
{
	template <typename INT_T>
	inline INT_T clamp_int_to_positive(INT_T signed_int);
	
	template <typename INT_T>
	inline void clamp_int_to_positive_ref(INT_T &signed_int); 

	template <typename INT_T>
	inline INT_T clamp_int_to_negative(INT_T signed_int);

	template <typename INT_T>
	inline void clamp_int_to_negative_ref(INT_T &signed_int);

	template <typename INT_T, typename UINT_T>
	inline INT_T clamp_uint_to_int(UINT_T unsigned_int);

	template <typename INT_T, typename UINT_T>
	inline void clamp_uint_to_int_ref(UINT_T &unsigned_int);
}

#include "utils.inl"

#endif /* UTILS_HPP_ */