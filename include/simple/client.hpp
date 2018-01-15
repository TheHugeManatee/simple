#pragma once

#include <zmq.h>
#include <string>
#include <memory>
#include "context_deleter.hpp"
#include "simple/generic_socket.hpp"

namespace simple
{
/**
 * @brief Creates a Client socket for a specific type of message.
 */
template <typename T>
class Client : public GenericSocket<T>
{
public:
  Client(const std::string& address)
    : GenericSocket<T>(zmq_socket(context_.get(), ZMQ_REQ))
  {
    GenericSocket<T>::connect(address);
  }

  /**
   * @brief Copy constructor for Client. Opens a new socket of the same type, connected to the same address.
   */
  Client(const Client& other)
    : GenericSocket<T>(zmq_socket(context_.get(), ZMQ_REQ))
  {
    GenericSocket<T>::connect(other.address_);
  }

  ~Client() {}
  /**
   * @brief Sends the request to a server and waits for an answer.
   * @param msg: SIMPLE class wrapper for Flatbuffer messages.
   */
  bool request(T& msg)
  {
    uint8_t* buffer = msg.getBufferData();
    int buffer_size = msg.getBufferSize();
    return request(buffer, buffer_size, msg);
  }

private:
  bool request(uint8_t* data, const int data_size, T& msg)
  {
    bool success{false};

    if (GenericSocket<T>::sendMsg(data, data_size, msg.getBuilderPointer(), "[SIMPLE Client] - "))
    {
      if (GenericSocket<T>::receiveMsg(msg, "[SIMPLE Client] - "))
      {
        success = true;
      }
    }
    return success;
  }
  static std::shared_ptr<void> context_;
};

template <typename T>
std::shared_ptr<void> Client<T>::context_(zmq_ctx_new(), contextDeleter);
}  // Namespace simple.
