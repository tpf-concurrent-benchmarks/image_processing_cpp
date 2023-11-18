#ifndef SIZE_WORKER_PROTOCOL_H
#define SIZE_WORKER_PROTOCOL_H

#include "nlohmann/json.hpp"
#include "zmq.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;

class Protocol
{
  public:
    Protocol(const std::string &pullPort);
    std::string receive();
    void close();

  private:
    zmq::context_t context_;
    zmq::socket_t receiver_;

    [[nodiscard]] zmq::message_t createZmqMessage(const json &message) const;
};

#endif // SIZE_WORKER_PROTOCOL_H
