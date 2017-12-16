#pragma once

#include <array>
#include <iostream>
#include "rotation_matrix.h"
#include "header.h"
#include "generic_message.h"
#include "generated/rotation_matrix_stamped_generated.h"

namespace simple_msgs
{
/**
 * @brief RotationMatrix: wrapper class arounf the RotationMatrixFbs generated code from flatbuffers.
 * The matrix is stored colo
 */
class RotationMatrixStamped : public GenericMessage
{
public:
  RotationMatrixStamped();
  RotationMatrixStamped(const Header&, const RotationMatrix&);
  RotationMatrixStamped(const uint8_t*);
  RotationMatrixStamped(const RotationMatrixStamped&);
  RotationMatrixStamped(RotationMatrixStamped&&);

  RotationMatrixStamped& operator=(const RotationMatrixStamped&);
  RotationMatrixStamped& operator=(RotationMatrixStamped&&);
  RotationMatrixStamped& operator=(const uint8_t*);

  inline bool operator==(const RotationMatrixStamped& rhs) const
  {
    return (rotation_matrix_ == rhs.rotation_matrix_ && header_ == rhs.header_);
  }
  inline bool operator!=(const RotationMatrixStamped& rhs) const { return !(*this == rhs); }
  friend std::ostream& operator<<(std::ostream&, const RotationMatrixStamped&);

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   * @return the buffer data.
   */
  uint8_t* getBufferData() const override;

  /**
   * @brief Returns the rotation matrix.
   */
  inline RotationMatrix& getRotationMatrix() { return rotation_matrix_; }
  inline const RotationMatrix& getRotationMatrix() const { return rotation_matrix_; }
  /**
   * @brief Returns the message Header.
   */
  inline Header& getHeader() { return header_; }
  inline const Header& getHeader() const { return header_; }
  /**
   * @brief Mofidies the matrix.
   * @param rotation_matrix:
   */
  inline void setRotationMatrix(const RotationMatrix&);

  /**
   * @brief Mofidies the header.
   * @param header:
   */
  inline void setHeader(const Header&);

  /**
   * @brief Rerturns an identifier of the message type generated by the flatbuffers.
   */
  static const char* getTopic() { return RotationMatrixStampedFbsIdentifier(); }
private:
  RotationMatrix rotation_matrix_{};
  Header header_{};
};
}  // Namespace simple_msgs.
