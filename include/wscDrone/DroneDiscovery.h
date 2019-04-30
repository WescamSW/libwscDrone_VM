/****************************************************************************//**
 * @file
 * @brief This file contains the DroneDiscovery class used for connecting to a
 * Bebop 2 over an IP network.
 * @ingroup wscDrone wscDrone
 * @author Steve Lascos
 * @date Feb. 1, 2019
 * @copyright CONFIDENTIAL and PROPRIETARY to L3 Technologies Wescam. This
 * source code is copyrighted. The source code may not be copied, reproduced,
 * translated, or reduced to any electronic medium or machine-readable form
 * without the prior written consent of L-3 Wescam. This source code is
 * confidential and proprietary to L-3 Wescam and may not be reproduced,
 * published, or disclosed to others without company authorization.
 ******************************************************************************/

#ifndef DRONEDISCOVERY_H_
#define DRONEDISCOVERY_H_

#include <unistd.h>
#include <functional>
#include <memory>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#include <libARDiscovery/ARDiscovery.h>

#ifdef __cplusplus
}
#endif

namespace wscDrone {

// Forward declare classes for friendship
class DroneController;

class DroneDiscovery {
public:
    DroneDiscovery() = delete;
    /// Construct an instance using the specified IP address
    /// @param ipAddress the IP address as a string
    DroneDiscovery(std::string ipAddress);
    ~DroneDiscovery(); //< default destructor

protected:
    friend DroneController;

    /// Get a raw pointer to the discovery device
    /// @returns a raw pointer to the ARSDK3 discovery device
    ARDISCOVERY_Device_t *getDiscoveryDevice () { return m_discoveryDevice; }

private:
    ARDISCOVERY_Device_t *m_discoveryDevice = nullptr; ///< raw pointer to ARSDK3 discovery device
    std::string           m_ipAddress;                 ///< string containing the drones IP address
};

}

#endif /* DRONEDISCOVERY_H_ */
