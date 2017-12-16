#pragma once

#include <array>
#include <iostream>

#include "generic_message.h"
#include "quaternion.h"
#include "header.h"
#include "generated/quaternion_stamped_generated.h"

namespace simple_msgs
{
/**
 * @brief Quaternion: wrapper class around the QuaternionFbs generated code from flatbuffers.
 */
class QuaternionStamped : public GenericMessage
{
public:
  QuaternionStamped();
  QuaternionStamped(const Header&, const Quaternion&);
  QuaternionStamped(const uint8_t*);
  QuaternionStamped(const QuaternionStamped&);
  QuaternionStamped(QuaternionStamped&&);

  QuaternionStamped& operator=(const QuaternionStamped&);
  QuaternionStamped& operator=(QuaternionStamped&&);
  QuaternionStamped& operator=(const uint8_t*);

  inline bool operator==(const QuaternionStamped& rhs) const
  {
    return (quaternion_ == rhs.quaternion_ && header_ == rhs.header_);
  }
  inline bool operator!=(const QuaternionStamped& rhs) const { return !(*this == rhs); }
  friend std::ostream& operator<<(std::ostream&, const QuaternionStamped&);

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   */
  uint8_t* getBufferData() const override;

  /**
   * @brief Returns the message Quaternion.
   * @return
   */
  inline Quaternion& getQuaternion() { return quaternion_; }
  inline const Quaternion& getQuaternion() const { return quaternion_; }
  /**
   * @brief Returns the message Hader.
   */
  inline Header& getHeader() { return header_; }
  inline const Header& getHeader() const { return header_; }
  /**
   * @brief Modifies the message Quaternion.
   */
  inline void setQuaternion(const Quaternion&);
  /**
   * @brief Modifies the message Header.
   */
  inline void setHeader(const Header&);
  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static const char* getTopic() { return QuaternionStampedFbsIdentifier(); }
private:
  Quaternion quaternion_{};
  Header header_{};
};
}  // Namespace simple_msgs.
