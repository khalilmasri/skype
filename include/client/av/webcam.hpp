#ifndef WEBCAM_HPP
#define WEBCAM_HPP

#include <opencv2/opencv.hpp>
#include "av_settings.hpp"

class Webcam
{
public:
  using WebcamFrames = std::vector<std::vector<uchar>>;

  Webcam();
  ~Webcam();
  [[nodiscard]] auto capture() -> WebcamFrames;
  [[nodiscard]] auto valid() const -> bool;

private:
  int                m_camera;
  cv::Mat            m_frame;
  cv::VideoCapture   m_capture;
  bool               m_valid = true;

  static VideoSettings *m_VIDEO_SETTINGS;
};

#endif // WEBCAM_HPP
