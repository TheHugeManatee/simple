/**
 * S.I.M.P.L.E. - Smart Intuitive Messaging Platform with Less Effort
 * Copyright (C) 2018 Salvatore Virga - salvo.virga@tum.de, Fernanda Levy Langsch - fernanda.langsch@tum.de
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SIMPLE_MSGS_STRING_H
#define SIMPLE_MSGS_STRING_H

#include <ostream>

#include "generic_message.h"
#include "generated/string_generated.h"

namespace simple_msgs
{
class String : public GenericMessage
{
public:
  // Constructors,
  String() = default;
  String(const std::string&);
  String(std::string&&);
  String(const char*);
  String(const uint8_t*);
  String(const String&);
  String(String&&) noexcept;

  // Copy operations.
  String& operator=(const String&);
  String& operator=(String&&) noexcept;
  String& operator=(const uint8_t*);

  // Relational operators.
  inline bool operator==(const String& rhs) const { return (data_ == rhs.data_); }
  inline bool operator!=(const String& rhs) const { return !(*this == rhs); }
  // Binary arithmetic operators
  String& operator+=(const String&);
  friend String operator+(String, const String&);

  // Stream extraction.
  friend std::ostream& operator<<(std::ostream& out, const String& s);

  /**
   * @brief Builds and returns the buffer accordingly to the values currently stored.
   */
  std::shared_ptr<flatbuffers::DetachedBuffer> getBufferData() const override;

  /**
   * @brief Returns the string information contained in the message.
   */
  inline std::string get() const { return data_; }
  /**
   * @brief Modifies the string information contained in the message.
   */
  inline void set(const std::string& data)
  {
    std::lock_guard<std::mutex> lock(mutex_);
    data_ = data;
  }

  /**
   * @brief Set the content to an empty string.
   */
  inline void clear() { data_.clear(); }
  /**
   * @brief Returns an identifier of the message type generated by the flatbuffers.
   */
  static inline const char* getTopic() { return StringFbsIdentifier(); }
private:
  std::string data_{""};
};
}  // Namespace simple_msgs.

#endif  // SIMPLE_MSGS_STRING_H
