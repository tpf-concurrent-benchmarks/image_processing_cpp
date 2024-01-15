#ifndef BROKER_PROTOCOL_H
#define BROKER_PROTOCOL_H

#include "zmq.hpp"
#include <iostream>
#include <string>

class Protocol
{
  public:
    Protocol(const std::string &pushPort, const std::string &pullPort);
    void send(const std::string &message);
    std::string receive();
    void close();

  private:
    zmq::context_t context_;
    zmq::socket_t sender_;
    zmq::socket_t receiver_;
    zmq::socket_t end_work_;
};

#endif // BROKER_PROTOCOL_H
