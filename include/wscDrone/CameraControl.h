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
#include "VideoDriver.h"

namespace wscDrone {

/// Set the type of photos. NOTE: Anything other than SNAPSHOT will interrupt video. It should
/// resume afterwards. Different phototypes take different amounts of time to take.
enum class PhotoType : unsigned {
    RAW = 0,  ///< RAW DNG format images. Also creates the JPEG FISHEYE image.
    JPEG_4_3, ///< JPEG 4:3 image
    SNAPSHOT, ///< JPEG 16:9 restricted FOV
    FISHEYE   ///< JPEG FISHEYE
};

enum class CameraState : unsigned {
    READY = 0,    ///< Camera is ready to take a picture
    BUSY,         ///< Camera is busy taking a picture
    NOT_AVAILABLE ///< Camera is not available
};

/// The CameraControl class permits the user to access the virtual tilt and pan
/// functions of the 180 degree FOV wide-angle camera.
class CameraControl {
public:
    CameraControl() = delete;

    /// Construct a CameraControl instance for the provided droneController
    /// @param droneController a smart pointer to an  instance of DroneController
    /// @param photoType Specifies what type of photos to provide
    CameraControl(std::shared_ptr<DroneController> droneController, std::shared_ptr<VideoDriver> videoDriver);

    // Default destructor
    ~CameraControl() {};

    /// Change the orientation of the camera
    /// @param tilt angle specified in degrees. Positive (negative) numbers tilt up (down)
    /// @param pan angle specified in degrees. Positive (negative) numbers pan to the right (left)
    void setTiltPan(float tilt, float pan);

    /// Set the camera looking forward at 0.0 degree tilt, 0.0 degrees pan
    void setForward();

    /// Sets the type of photo taken when capturePhoto() is called.
    /// @param photoType specifies the type of photo, either JPEG or RAW
    void setPhotoType(PhotoType photoType);

    /// Take a picture with the camera. You will need to download the photo over FTP.
    void capturePhoto();

    /// Get the last known state of the camera
    /// @returns the enumerated camera state
    CameraState getCameraState() { return m_cameraState; }

    /// This function is used by the callback to set the camera state when it receives an update
    /// from the drone
    /// @param cameraState An enumerate of the state
    void setCameraState(CameraState cameraState);



private:
    Semaphore m_photoSem;
    ARCONTROLLER_Device_t *m_deviceController = nullptr; ///< smart pointer to a DeviceController
    PhotoType m_photoType = PhotoType::JPEG_4_3;
    CameraState m_cameraState;
    bool m_photoInProgress = false;
    std::shared_ptr<VideoDriver> m_videoDriver = nullptr;
    unsigned m_outstandingPhotos = 0;

    void m_notifyPhotoComplete();
    bool m_waitPhotoComplete();
};

}

#endif /* CAMERACONTROL_H_ */
