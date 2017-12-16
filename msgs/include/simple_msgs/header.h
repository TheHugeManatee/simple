#pragma once

#include <ostream>

#include "generic_message.h"
#include "generated/header_generated.h"

namespace simple_msgs
{
/**
 * @brief Header: wrapper class around the HeaderFbs generated code from flatbuffers.
 */
class Header : public GenericMessage
{
public:
  Header();
  Header(int, const std::string&, double);
  Header(const uint8_t*);
  Header(const Header&);
  Header(Header&&);

  Header& operator=(const Header&);
  Header& operator=(Header&&);
  Header& operator=(const uint8_t*);

  inline bool operator==(const Header& rhs) const
  {
    return (seq_n_ == rhs.seq_n_ && frame_id_ == rhs.frame_id_ && timestamp_ == rhs.timestamp_);
  }
  inline bool operator!=(const Header& rhs) const { return !(*this == rhs); }
  friend std::ostream& operator<<(std::ostream& out, const Header& h);

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   */
  uint8_t* getBufferData() const override;

  /**
   * @brief Returns the sequence number of the message.
   */
  inline int getSequenceNumber() { return seq_n_; }
  inline const int getSequenceNumber() const { return seq_n_; }
  /**
   * @brief Returns the frame id of the message.
   */
  inline std::string getFrameID() { return frame_id_; }
  inline const std::string getFrameID() const { return frame_id_; }
  /**
   * @brief Returns the timestamp of the message.
   */
  inline double getTimestamp() { return timestamp_; }
  inline const double getTimestamp() const { return timestamp_; }
  /**
   * @brief Modifies the sequence number of the message.
   */
  void setSequenceNumber(int);

  /**
   * @brief Modifies the frame id of the message.
   */
  void setFrameID(const std::string&);

  /**
   * @brief Modifies the timestamp of the message.
   * @param timestamp Seconds since the epoch, when the data in the message was generated.
   */
  void setTimestamp(double);

  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static inline const char* getTopic() { return HeaderFbsIdentifier(); }
private:
  int seq_n_{0};
  std::string frame_id_{""};
  double timestamp_{0.0};
};
}  // Namespace simple_msgs.
