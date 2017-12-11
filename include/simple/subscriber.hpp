#pragma once

#include <zmq.h>
#include <string>
#include <thread>

#include "simple/generic_socket.hpp"

namespace simple
{
/**
 * @brief Creates a subscriber socket for a specific type of message.
 */
template <typename T>
class Subscriber : public GenericSocket<T>
{
public:
  /**
   * @brief Creates a ZMQ_SUB socket and connects it to the given address.
   * The given callback runs on a dedicated thread.s
   * @param Address to subscriber to, in the form: tcp://HOSTNAME:PORT. e.g tcp://localhost:5555.
   * @param User defined callback function for incoming messages.
   * @param Time the subscriber will block the thread waiting for a message. In milliseconds.
   */
  Subscriber<T>(const std::string& address, const std::function<void(const T&)>& callback, int timeout = 100)
    : GenericSocket<T>(zmq_socket(context_, ZMQ_SUB))
    , callback_(callback)
  {
    GenericSocket<T>::connect(address);
    GenericSocket<T>::filter();
    GenericSocket<T>::setTimeout(timeout);

    // Start the callback thread.
    subscriber_thread_ = std::thread(&Subscriber::subscribe, this);
  }

  ~Subscriber<T>()
  {
    alive_ = false;             //< Stop the subscription loop.
    subscriber_thread_.join();  //< Wait for the subscriber thead.
    zmq_ctx_term(context_);     //< Terminate the context.
  }

private:
  /**
   * @brief Waits for a message to be published to the connected port,
   * Calls the user callback with an instance of T obtained by a publisher.
   */
  void subscribe()
  {
    while (alive_)
    {
      T msg;
      if (GenericSocket<T>::receiveMsg(msg, "[SIMPLE Subscriber] - "))
      {
        callback_(msg);
      }
    }
  }

  std::thread subscriber_thread_;
  bool alive_{true};
  std::function<void(const T&)> callback_;
  static void* context_;
};

template <typename T>
void* Subscriber<T>::context_(zmq_ctx_new());

}  // Namespace simple.