#include "av_stream.hpp"
#include "logger.hpp"

AVStream::AVStream() : m_input(m_input_queue, AudioDevice::Input) {}

void AVStream::start() {
  if (m_status == Stopped) {
    m_input.open(); // audio
    AudioDevice::wait(25);
    m_status = Started;

  } else {
    LOG_ERR("Could not START start AVStream because its status is: %s",
            m_status == Invalid ? "'Invalid'." : "'Started'.")
  }
}

void AVStream::stream(DataCallback &t_callback) {

  while (m_status == Started) {


    // take a frame and wait 1 frame worth of time
    Webcam::WebcamFrames encoded_video = m_webcam.capture();

    // convert first audio buffer from the audio queue.
    Data::DataVector encoded_audio = m_converter.encode(m_input_queue);

    // check if conversion and frame capture were successful
    validate();

    t_callback(std::move(encoded_video), std::move(encoded_audio));
  }
}

void AVStream::stop() {
  if (m_status == Started) {
    m_input.close();
    m_status = Stopped;
  } else {
    LOG_ERR("Cannot STOP AVStream because its status is: %s",
            m_status == Invalid ? "'Invalid'." : "'Stopped'.")
  }
}

void AVStream::validate() {
  if (!(m_webcam.valid() && m_converter.valid())) {
    m_status = Invalid;
  }
};