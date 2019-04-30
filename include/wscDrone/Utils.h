/****************************************************************************//**
 * @file
 * @brief This file contains a misc helper functions
 * @ingroup wscDrone wscDrone
 * @author Steve Lascos
 * @date Feb. 7, 2019
 * @copyright CONFIDENTIAL and PROPRIETARY to L3 Technologies Wescam. This
 * source code is copyrighted. The source code may not be copied, reproduced,
 * translated, or reduced to any electronic medium or machine-readable form
 * without the prior written consent of L-3 Wescam. This source code is
 * confidential and proprietary to L-3 Wescam and may not be reproduced,
 * published, or disclosed to others without company authorization.
 ******************************************************************************/

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <cmath>

namespace wscDrone {

constexpr float PI_DIV_2_F   = atan(1)*2;     ///< 90 degress
constexpr float PI_F         = atan(1)*4;     ///< 180 degress
constexpr float PI_3_DIV_2_F = atan(1)*4*3/2; ///< 270 degress

/// Create a blocking sleep function, specified in seconds
/// @param seconds time to sleep in seconds
void waitSeconds(int seconds);

/// Create a blocking sleep function, specified in milliseconds
/// @param milliseconds time to sleep in milliseconds
void waitMilliseconds(int milliseconds);

/// Convert degrees to radians
/// @param degrees the angle in degrees
/// @returns the angle converted to radians
float degressToRadians(float degrees);

} // wscDrone

#endif /* SRC_UTILS_H_ */
