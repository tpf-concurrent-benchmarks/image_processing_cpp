#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "nlohmann/json.hpp"
#include "zmq.hpp"
#include <string>
#include <iostream>

using json = nlohmann::json;

class Protocol
{
public:
    Protocol(const std::string &pushPort);
    void send(const std::string &message);
    void close();

private:
    zmq::context_t context_;
    zmq::socket_t sender_;

    [[nodiscard]] zmq::message_t createZmqMessage(const json &message) const;
};


#endif //PROTOCOL_H
