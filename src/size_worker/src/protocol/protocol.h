#ifndef SIZE_WORKER_PROTOCOL_H
#define SIZE_WORKER_PROTOCOL_H

#include "zmq.hpp"
#include <iostream>
#include <string>

class Protocol
{
  public:
    Protocol(const std::string &brokerHost, const std::string &managerHost, const std::string &pushPort,
             const std::string &pullPort);
    std::string receive();
    void send(const std::string &message);
    void close();

  private:
    zmq::context_t context_;
    zmq::socket_t receiver_;
    zmq::socket_t sender_;
};

#endif // SIZE_WORKER_PROTOCOL_H
