/**
 * @file	tractor_pch.hpp
 * @brief	Precompiled header file.
 * 
 * @author	Erlend Elias Isachsen
 * @date	25.07.2023
 * 
*/

#ifndef TRACTOR_PCH_HPP_
#define TRACTOR_PCH_HPP_

#if CMAKE_BUILD_TYPE == Debug
#define TRAC_DEBUG
#else
#define TRAC_RELEASE
#endif

// Standard library header includes
#include <stdio.h>
#include <iostream>
#include <memory>
#include <algorithm>
#include <functional>

#include <cstdint>
#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>

// Project header includes
#include "tractor/events.hpp"

#endif // TRACTOR_PCH_HPP_ 