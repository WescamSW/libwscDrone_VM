/****************************************************************************//**
 * @file
 * @brief This file contains the Pilot class responsible for moving the drone.
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

#ifndef PILOT_H_
#define PILOT_H_

#include <memory>

#ifdef __cplusplus
extern "C" {
#endif

#include <libARController/ARController.h>

#ifdef __cplusplus
}
#endif

#include "DroneController.h"

namespace wscDrone {

constexpr float RIGHT_90_DEGREES  =   90.0f;
constexpr float LEFT_90_DEGREES   =  -90.0f;
constexpr float RIGHT_180_DEGREES =  180.0f;
constexpr float LEFT_180_DEGREES  = -180.0f;
constexpr float RIGHT_270_DEGREES =  270.0f;
constexpr float LEFT_270_DEGREES  = -270.0f;

/// List of drone flying states
enum class FlyingState : int {
    LANDED = 0,     ///< drone is landed
    TAKING_OFF = 1, ///< drone is in the process of taking off
    HOVERING = 2,   ///< drone is currently hovering, holding position
    FLYING = 3,     ///< drone is currently flying (moving)
    LANDING = 4,     ///< drone is in the process of landing
    EMERGENCY = 5,     ///< drone has something gone bad right now
    MOTOR_SPINUP = 7,     ///< drone has motors starting and spinning up
};

/// List of drone movement directions
enum class MoveDirection : int {
    UP      = 0, ///< move drone upward
    DOWN    = 1, ///< move drone downwards
    FORWARD = 2, ///< move drone forward in relation to current heading
    BACK    = 3, ///< move drone backward in relation to current heading
    RIGHT   = 4, ///< move drone right in relation to current heading
    LEFT    = 5, ///< move drone left in relation to current heading
};

/// This class provides an API to control the movement of the drone.
class Pilot {
public:

    Pilot() = delete;
    /// Construct an instance for the specified DroneController
    /// @param droneController smart pointer to  a DroneController instance
    /// @param initialFlightAltitude specifies the drones initial altitdue in metres after takeoff
    Pilot(std::shared_ptr<wscDrone::DroneController> droneController, float initialFlightAltitude);
    ~Pilot() {} ///< default destructor

    /// get the current RAW ARSDK3 flying state of the drone
    /// @returns the current ARSDK3 flying state of the drone
    eARCOMMANDS_ARDRONE3_PILOTINGSTATE_FLYINGSTATECHANGED_STATE getFlyingStateRaw();

    /// Get the current flying state
    /// @returns the current flying state
    FlyingState getFlyingState() { return m_flyingState; }

    void takeOff(); ///< instruct the drone to take off
    void land();    ///< instruct the drone to land

    /// THIS FUNCTION IS AN EMERGENCY ENGINE CUT. THE DRONE WILL FALL!!!
    void CUT_THE_MOTORS();

    /// Instruct the drone to move to a position relative to it's current position.
    /// @param dx displacement in meters to the right (positive) or left (negative)
    /// @param dy displacement in meters forward (positive) or backwards (negative)
    /// @param heading desired orientation of the drone in degrees, 0 is the current drone heading.
    /// Positive numbers are clockwise rotation.
    /// @param wait when true the call blocks until the move is done
    /// @returns true when the movement is completed, false if a timeout occurs when waiting for the completion event
    bool moveRelativeMetres(float dx, float dy, float heading = 0.0f, bool wait = true);

#ifndef RESTRICTED_ALTITUDE
    /// THIS FUNCTION IS NOT AVAILBLE TO HACKATHON CONTESTANTS

    /// Instruct the drone to move to a position relative to it's current position.
    /// @param dx displacement in meters to the right (positive) or left (negative)
    /// @param dy displacement in meters forward (positive) or backwards (negative)
    /// @param heading desired orientation of the drone in degrees, 0 is the current drone heading.
    /// Positive numbers are clockwise rotation.
    /// @param wait when true the call blocks until the move is done
    /// @returns true when the movement is completed, false if a timeout occurs when waiting for the completion event
    bool moveRelativeMetresRestricted(float dx, float dy, float dz, float heading = 0.0f, bool wait = true);
#endif
    
    /// Instruct the drone to move in the specified direction
    /// @param direction direction to move the drone, will move MOVEMENT_STEP distance
    void moveDirection(MoveDirection direction);

    /// Set the drones orientation without moving
    /// @param heading the desired orientation in degrees, 0 degrees is the current heading.
    /// Positive numbers are clockwise.
    void setHeading(float heading);

    /// Set the flying state of the drone. NOTE: this is typically called within a callback when the drone
    /// state changes.
    /// @param state the flying state of the drone
    /// @param debug when true, verbose debug messages are printed
    void setFlyingState(int state, bool debug = false);

    /// Call this function to notify the Pilot class that a Move has been completed. Typically called from
    /// a callback when the move-complete event is received
    void notifyMoveComplete();

    /// Call this funnction after executing a move command to block the thread until the move is complete.
    bool waitMoveComplete();

private:
    Semaphore moveSem;  ///< A semaphore to sync move events between this thread and the callback thread
    ARCONTROLLER_Device_t *m_deviceController = nullptr; ///< smart pointer to DeviceController instance
    FlyingState m_flyingState = FlyingState::LANDED; ///< current flying state of the drone
    float m_initialFlightAltitude = 0.0f; ///< initial altitude after takeoff

    /// Instruct the drone to move to a position relative to it's current position.
    /// @param dx displacement in meters to the right (positive) or left (negative)
    /// @param dy displacement in meters forward (positive) or backwards (negative)
    /// @param dz displacement in meters down (positive) or up (negative)
    /// @param heading desired orientation of the drone in degrees, 0 is the current drone heading.
    /// @param wait when true the call blocks until the move is done
    /// Positive numbers are clockwise rotation.
    /// @returns true when the movement is completed, false if a timeout occurs when waiting for the completion event
    bool m_moveRelativeMetres(float dx, float dy, float dz, float heading = 0.0, bool wait = true);

};

} // wscDrone

#endif /* PILOT_H_ */
