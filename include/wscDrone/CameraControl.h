/****************************************************************************//**
 * @file
 * @brief This file contains the CameraControl class provided a limited amount
 * of access to the Bebop 2 camaera system.
 * @ingroup wscDrone wscDrone
 * @author Steve Lascos
 * @date Feb. 4, 2019
 * @copyright CONFIDENTIAL and PROPRIETARY to L3 Technologies Wescam. This
 * source code is copyrighted. The source code may not be copied, reproduced,
 * translated, or reduced to any electronic medium or machine-readable form
 * without the prior written consent of L-3 Wescam. This source code is
 * confidential and proprietary to L-3 Wescam and may not be reproduced,
 * published, or disclosed to others without company authorization.
 ******************************************************************************/

#ifndef CAMERACONTROL_H_
#define CAMERACONTROL_H_

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

enum class PhotoType {
    RAW = 0, ///< RAW DNG format images
    JPEG     ///< JPEG compressed images
};

/// The CameraControl class permits the user to access the virtual tilt and pan
/// functions of the 180 degree FOV wide-angle camera.
class CameraControl {
public:
    CameraControl() = delete;

    /// Construct a CameraControl instance for the provided droneController
    /// @param droneController a smart pointer to an  instance of DroneController
    /// @param photoType Specifies what type of photos to provide
    CameraControl(std::shared_ptr<DroneController> droneController, PhotoType photoType);

    // Default destructor
    ~CameraControl() {};

    /// Change the orientation of the camera
    /// @param tilt angle specified in degrees. Positive (negative) numbers tilt up (down)
    /// @param pan angle specified in degrees. Positive (negative) numbers pan to the right (left)
    void setTiltPan(float tilt, float pan);

    /// Set the camera looking forward at 0.0 degree tilt, 0.0 degrees pan
    void setForward();

    /// Take a picture with the camera. You will need to download the photo over FTP.
    void capturePhoto();

private:
    ARCONTROLLER_Device_t *m_deviceController = nullptr; ///< smart pointer to a DeviceController
    PhotoType m_photoType;

};

}

#endif /* CAMERACONTROL_H_ */
