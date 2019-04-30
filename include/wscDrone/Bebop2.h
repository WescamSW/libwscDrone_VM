/****************************************************************************//**
 * @file
 * @brief Bebop2 is an encapsulatino class providing a single user-API into the
 * Bebop 2 AR Software Development Kit 3.
 * @ingroup wscDrone wscDrone
 * @author Steve Lascos
 * @date Feb. 3, 2019
 * @copyright CONFIDENTIAL and PROPRIETARY to L3 Technologies Wescam. This
 * source code is copyrighted. The source code may not be copied, reproduced,
 * translated, or reduced to any electronic medium or machine-readable form
 * without the prior written consent of L-3 Wescam. This source code is
 * confidential and proprietary to L-3 Wescam and may not be reproduced,
 * published, or disclosed to others without company authorization.
 ******************************************************************************/

#ifndef BEBOP2_H_
#define BEBOP2_H_

#include <string>
#include <memory> // for shared_ptr

#include "Semaphore.h"
#include "DroneDiscovery.h"
#include "DroneController.h"
#include "CameraControl.h"
#include "Pilot.h"
#include "VideoDecoder.h"
#include "VideoDriver.h"

namespace wscDrone {

/// Provide symbolic names as "callsigns" to identify the drones.
enum class Callsign : unsigned {
    ALPHA      = 0, ///< Low altitude drone
    BRAVO      = 1, ///< Mid-altitude drone
    CHARLIE    = 2, ///< High-altitude drone
    LONE_WOLF  = 3  ///< stand alone drone creating it's own WIFI network
};

/***************************************************************************//**
 * Primary Wescam interface to the Bebop 2 drone. This class exposes only the
 * functionality required for based navigiation and video/camera activities.
 ******************************************************************************/
class Bebop2 {
public:
    Bebop2() = delete;
    /// Construct a Bebop2 control instance using the specified IP address.
    /// @param ipAddress the IP address of the drone you wish to control.
    /// @param frame the VideoFrame object to associate with the drone
    Bebop2(std::string ipAddress, std::shared_ptr<VideoFrame> frame);

    /// Construct a Bebop2 control instance using the Callsign
    /// @param callsign the enumerated label for the desired drone to control
    /// @param frame the VideoFrame object to associate with the drone
    Bebop2(Callsign callsign, std::shared_ptr<VideoFrame> frame);

    /// Default destructor
    ~Bebop2() {}

    /// Get a shared pointer to the DroneController class
    /// @returns shared pointer to drone controller class
    std::shared_ptr<DroneController> getDroneController() { return m_droneController; }

    /// Get a shared pointer to the CameraControl class
    /// @returns a shared pointer to the camera control class.
    std::shared_ptr<CameraControl>   getCameraControl()   { return m_camera; }

    /// Get a shared pointer to the Pilot class
    /// @returns a shared pointer to the piloting class.
    std::shared_ptr<Pilot>           getPilot()           { return m_pilot; }

    /// Get a shared pointer to the drone state semaphore
    /// @returns a shared pointer to sempahore
    std::shared_ptr<Semaphore>       getStateSemaphore()  { return m_droneController->getStateSemaphore(); }

    /// Get a shared pointer to the VideoDriver class
    /// @returns a shared pointer to the video driver class
    std::shared_ptr<VideoDriver>     getVideoDriver()     { return m_video; }

    /// Get the current battery level
    /// @returns battery level 0 to 100.
    unsigned getBatteryLevel() { return m_batteryLevel; }

    /// Sets the battery level. This function is used by a callback within the library. Users should not call
    /// it directly.
    void setBatteryLevel(unsigned level) { m_batteryLevel = level; }

    /// Get the IP address of the drone
    /// @returns IP address as a string
    std::string getIpAddress() { return m_ipAddress; }

private:
    Callsign    m_callsign;         ///< callsign of the drone
    std::string m_ipAddress;        ///< ipAddress of the drone under control
    unsigned    m_batteryLevel = 0; ///< battery level, 0 to 100
    std::shared_ptr<DroneDiscovery>  m_droneDiscovery  = nullptr; ///< shared pointer to DroneDiscovery class
    std::shared_ptr<DroneController> m_droneController = nullptr; ///< shared pointer to DroneController class
    std::shared_ptr<CameraControl>   m_camera          = nullptr; ///< shared pointer to CameraControl class
    std::shared_ptr<Pilot>           m_pilot           = nullptr; ///< shared pointer to Pilot class
    std::shared_ptr<VideoDriver>     m_video           = nullptr; ///< shared pointer to VideoDriver class

    /// Provide a default callback for incoming commands
    static void m_onCommandReceivedDefault(eARCONTROLLER_DICTIONARY_KEY commandKey, ARCONTROLLER_DICTIONARY_ELEMENT_t *elementDictionary, void *customData);

};

} // wscDrone

#endif /* BEBOP2_H_ */
