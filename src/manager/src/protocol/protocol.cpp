#include "protocol.h"

Protocol::Protocol(const std::string &pushPort)
{
    context_ = zmq::context_t(2);
    sender_ = zmq::socket_t(context_, ZMQ_PUSH);
    sender_.bind("tcp://*:" + pushPort);
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
    sender_.close();
    context_.close();
}
