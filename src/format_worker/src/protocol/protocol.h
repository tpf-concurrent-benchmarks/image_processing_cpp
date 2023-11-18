#ifndef FORMAT_WORKER_PROTOCOL_H
#define FORMAT_WORKER_PROTOCOL_H

#include "nlohmann/json.hpp"
#include "zmq.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;

class Protocol
{
  public:
    Protocol(const std::string &managerHost, const std::string &brokerHost, const std::string &pushPort,
             const std::string &pullPort);
    void send(const std::string &message);
    std::string receive();
    void close();

  private:
    zmq::context_t context_;
    zmq::socket_t sender_;
    zmq::socket_t receiver_;

    [[nodiscard]] zmq::message_t createZmqMessage(const json &message) const;
};

#endif // FORMAT_WORKER_PROTOCOL_H
