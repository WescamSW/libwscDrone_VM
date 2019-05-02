/****************************************************************************//**
 * @file
 * @brief This file contains a VideoDriver class to interact with the video
 * system on the Bebop 2 drone.
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

#ifndef VIDEODRIVER_H_
#define VIDEODRIVER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <libswscale/swscale.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavutil/imgutils.h>

#ifdef __cplusplus
}
#endif

#include "VideoFrame.h"
#include "DroneController.h"
#include "VideoDecoder.h"

namespace wscDrone {

constexpr unsigned BEBOP2_STREAM_WIDTH  = 856;
constexpr unsigned BEBOP2_STREAM_HEIGHT = 480;

/// alias for ARSDK3 ARCONTROLLER_Stream_DecoderConfigCallback_t
using VideoDecoderConfigCallback = ARCONTROLLER_Stream_DecoderConfigCallback_t;

/// alias for ARSDK3 ARCONTROLLER_Stream_DidReceiveFrameCallback_t
using VideoFrameReceivedCallback = ARCONTROLLER_Stream_DidReceiveFrameCallback_t;

enum class VideoState : unsigned {
    STOPPED = 0,      ///< video is stopped
    STARTED = 1,      //< video is started
    NOT_AVAILABLE = 2 //< video is not available
};

/// This driver extends the VideoDecoder class created from ROS (Robot Operating System).
class VideoDriver : public bebop_driver::VideoDecoder {
public:
    VideoDriver() = delete;
    /// Construct a VideoDriver with an associated DroneController
    /// @param droneController smart pointer to a DroneController instance
    /// @param frame a smart pointer to a VideoFrame object for streaming video
    VideoDriver(std::shared_ptr<wscDrone::DroneController> droneController, std::shared_ptr<VideoFrame> frame);
    ~VideoDriver(); ///< default destructor

    /// Register the callbacks for the video decoder and new frame
    /// @param decoderCallback the callback function to execute when the drones H.264 encoder changes
    /// @param videoCallback the callback function to exectue when a new frame is received
    /// @param customData a raw pointer to the actual VideoDriver instance
    void registerVideoCallback(const VideoDecoderConfigCallback &decoderCallback, const VideoFrameReceivedCallback &videoCallback, void *customData);

    /// Get a smart pointer to the mutex guarding the video buffer
    /// @returns smart pointer to a mutex
    std::shared_ptr<std::mutex> getBufferMutex() { return m_bufferGuard; }

    /// Set a smart pointer to the VideoFrame object used by the video driver. This replaces the one provided during construction.
    /// @param frame a smart pointer to an instance of VideoFrame
    void setFrame(std::shared_ptr<VideoFrame> frame);

    /// Get a smart pointer to the currently used VideoFrame
    /// @returns a smart pointer to a VideoFrame instance
    std::shared_ptr<VideoFrame> getFrame() { return m_frame; }


    /// Starts the H.264 video streaming interface on the drone
    void start();
    /// Stops the H.264 video streaming interface on the drone
    void stop();

    /// Get the last known state of the video
    /// @returns the enumerated video state
    VideoState getVideoState() { return m_videoState; }

    /// This function is used by the callback to set the video state when it receives an update
    /// from the drone
    /// @param videoState An enumerate of the state
    void setVideoState(VideoState videoState) { m_videoState = videoState; }

private:
    ARCONTROLLER_Device_t *m_deviceController = nullptr; ///< raw pointer to the ARSDK device controller
    std::shared_ptr<std::mutex> m_bufferGuard = nullptr; ///< shared pointer to a mutex protecting the video frame object
    std::shared_ptr<VideoFrame> m_frame       = nullptr; ///< shared pointer to a VideoFrame object
    VideoState m_videoState;

    /// Default callback for handling decoder changes
    /// @param codec ARSDK3 codec
    /// @param customData a pointer to an instance of VideoDriver
    static eARCONTROLLER_ERROR m_decoderConfigCallDefault(ARCONTROLLER_Stream_Codec_t codec, void *customData);

    /// Default callback for handling new video frames received
    /// @param frame pointer to a ARSDK3 frame
    /// @param customData a pointer to an instance of VideoDriver
    static eARCONTROLLER_ERROR m_onFrameReceivedDefault(ARCONTROLLER_Frame_t *frame, void *customData);
};

}

#endif /* VIDEODRIVER_H_ */
