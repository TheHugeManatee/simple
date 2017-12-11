#pragma once

#include <algorithm>
#include <ostream>

#include "generic_message.h"

namespace simple_msgs
{
template <typename T>
class NumericType : public GenericMessage
{
public:
  // Constructors.

  NumericType()
    : GenericMessage()
  {
  }

  NumericType(T data)
    : GenericMessage()
    , data_(data)
  {
  }

  /**
   * @brief Constructor from the buffer data, implementation is specific to the template specialization.
   */
  NumericType(const uint8_t* data);

  // Copy operations.

  NumericType(const NumericType& other)
    : NumericType(other.data_)
  {
  }

  NumericType& operator=(const NumericType& rhs)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    std::swap(data_, rhs.data_);
    modified_ = true;
    return *this;
  }

  // Move operations.

  NumericType(NumericType&& other)
    : NumericType(std::move(other.data_))
  {
  }

  NumericType& operator=(NumericType&& rhs)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    data_ = std::move(rhs.data_);
    modified_ = true;
    return *this;
  }

  // Relational operators.
  inline bool operator==(const NumericType& rhs) { return data_ == rhs.data_; }
  inline bool operator!=(const NumericType& rhs) { return !(*this == rhs); }
  inline bool operator<(const NumericType& rhs) { return data_ < rhs.data_; }
  inline bool operator>(const NumericType& rhs) { return rhs < *this; }
  inline bool operator<=(const NumericType& rhs) { return !(*this > rhs); }
  inline bool operator>=(const NumericType& rhs) { return !(*this < rhs); }
  // Increment and decrement operators.

  NumericType& operator--()
  {
    --data_;
    return *this;
  }

  NumericType operator--(int)
  {
    const NumericType old(*this);
    --(*this);
    return old;
  }

  NumericType& operator++()
  {
    ++data_;
    return *this;
  }

  NumericType operator++(int)
  {
    const NumericType old(*this);
    ++(*this);
    return old;
  }

  // Binary arithmetic operatorss

  NumericType& operator+=(const NumericType& rhs)
  {
    data_ += rhs.data_;
    return *this;
  }

  friend NumericType operator+(NumericType lhs, const NumericType& rhs)
  {
    lhs += rhs;
    return lhs;
  }

  NumericType& operator-=(const NumericType& rhs)
  {
    data_ -= rhs.data_;
    return *this;
  }

  friend NumericType operator-(NumericType lhs, const NumericType& rhs)
  {
    lhs -= rhs;
    return lhs;
  }

  NumericType& operator*=(const NumericType& rhs)
  {
    data_ *= rhs.data_;
    return *this;
  }

  friend NumericType operator*(NumericType lhs, const NumericType& rhs)
  {
    lhs *= rhs;
    return lhs;
  }

  NumericType& operator/=(const NumericType& rhs)
  {
    data_ /= rhs.data_;
    return *this;
  }

  friend NumericType operator/(NumericType lhs, const NumericType& rhs)
  {
    lhs /= rhs;
    return lhs;
  }

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   * @return the buffer data.
   */
  uint8_t* getBufferData() const;

  /**
   * @brief Set the double value.
   */
  void set(T data);

  /**
   * @brief Get the double value.
   */
  T get() const { return data_; }
  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static inline const char* getTopic();

  //  Stream extraction.
  template <typename Tn>
  friend std::ostream& operator<<(std::ostream& out, const NumericType<Tn>& obj);

private:
  T data_{0};
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const NumericType<T>& obj)
{
  out << obj.data_;
  return out;
}
}  // Namespace simple_msgs.