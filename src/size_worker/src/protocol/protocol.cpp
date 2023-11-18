#include "protocol.h"

Protocol::Protocol(const std::string &brokerHost, const std::string &pullPort)
{
    context_ = zmq::context_t(2);
    receiver_ = zmq::socket_t(context_, ZMQ_PULL);
    receiver_.connect("tcp://" + brokerHost + ":" + pullPort);
}

std::string Protocol::receive()
{
    zmq::message_t message;
    const zmq::recv_result_t &anOptional = receiver_.recv(message);
    if (!anOptional.has_value())
    {
        return "Error message";
    }
    return std::string(static_cast<char *>(message.data()), message.size());
}

void Protocol::close()
{
    receiver_.close();
    context_.close();
}