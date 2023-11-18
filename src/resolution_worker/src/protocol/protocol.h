#ifndef RESOLUTION_WORKER_PROTOCOL_H
#define RESOLUTION_WORKER_PROTOCOL_H

#include "zmq.hpp"
#include <iostream>
#include <string>

class Protocol
{
  public:
    Protocol(const std::string &brokerFromFormat, const std::string &brokerFromSize, const std::string &pushPort,
             const std::string &pullPort);
    void send(const std::string &message);
    std::string receive();
    void close();

  private:
    zmq::context_t context_;
    zmq::socket_t sender_;
    zmq::socket_t receiver_;
};

#endif // RESOLUTION_WORKER_PROTOCOL_H
