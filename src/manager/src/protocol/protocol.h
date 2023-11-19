#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "zmq.hpp"
#include <iostream>
#include <string>

class Protocol
{
  public:
    Protocol(const std::string &pushPort);
    void send(const std::string &message);
    void close();

  private:
    zmq::context_t context_;
    zmq::socket_t sender_;
};

#endif // PROTOCOL_H
