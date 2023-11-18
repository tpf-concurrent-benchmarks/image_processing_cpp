#ifndef RESOLUTION_WORKER_PROTOCOL_H
#define RESOLUTION_WORKER_PROTOCOL_H


#include "nlohmann/json.hpp"
#include "zmq.hpp"
#include <string>
#include <iostream>

using json = nlohmann::json;

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

    [[nodiscard]] zmq::message_t createZmqMessage(const json &message) const;
};


#endif //RESOLUTION_WORKER_PROTOCOL_H
