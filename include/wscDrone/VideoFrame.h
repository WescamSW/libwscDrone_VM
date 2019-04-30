/*
 * VideoFrame.h
 *
 *  Created on: Apr 15, 2019
 *      Author: slascos
 */

#ifndef SRC_VIDEOFRAME_H_
#define SRC_VIDEOFRAME_H_

/// Abstract class to define the interface for a video frame object.
/// @details This class specifies the functions that must be provided by a child class
/// in order to work with the wscDrone library.
class VideoFrame {
public:
    VideoFrame() = delete;

    /// Construct a video frame object of specified height and width.
    VideoFrame(unsigned height, unsigned width) {}
    virtual ~VideoFrame() = default;

    /// Get the height of the VideoFrame object
    /// @returns the height in lines
    virtual unsigned getHeight()         = 0;

    /// Get the width of the VideoFrame object
    /// @returns the width in pixels
    virtual unsigned getWidth()          = 0;

    /// Get raw pointer to the underlying video data buffer
    /// @returns a char* pointer to the raw pixel bytes
    virtual char*    getRawPointer()     = 0;

    /// Get the size in bytes of the underlying vidoe data buffer
    /// @returns the size in bytes
    virtual size_t   getFrameSizeBytes() = 0;
};

#endif /* SRC_VIDEOFRAME_H_ */
