#include "protocol.h"

Protocol::Protocol(const std::string &brokerHost, const std::string &managerHost, const std::string &pushPort,
                   const std::string &pullPort)
{
    context_ = zmq::context_t(2);
    receiver_ = zmq::socket_t(context_, ZMQ_PULL);
    sender_ = zmq::socket_t(context_, ZMQ_PUSH);
    receiver_.connect("tcp://" + brokerHost + ":" + pullPort);
    sender_.connect("tcp://" + managerHost + ":" + pushPort);
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

void Protocol::send(const std::string &message)
{
    zmq::message_t zmqMessage(message.size());
    memcpy(zmqMessage.data(), message.c_str(), message.size());

    const zmq::send_result_t &anOptional = sender_.send(zmqMessage, zmq::send_flags::none);
    if (!anOptional.has_value())
    {
        std::cout << "Error sending message" << std::endl;
    }
}

void Protocol::close()
{
    receiver_.close();
    context_.close();
}