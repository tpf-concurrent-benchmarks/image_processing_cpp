#include <constants.h>
#include "protocol.h"

Protocol::Protocol(const std::string &pushPort, const std::string &pullPort)
{
    context_ = zmq::context_t(3);
    sender_ = zmq::socket_t(context_, ZMQ_PUSH);
    receiver_ = zmq::socket_t(context_, ZMQ_PULL);
    end_work_ = zmq::socket_t(context_, ZMQ_PUB);
    sender_.bind("tcp://*:" + pushPort);
    receiver_.bind("tcp://*:" + pullPort);
    end_work_.bind("tcp://*:" + Constants::END_WORK_PORT);

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

void Protocol::sendStopMessage(const std::string &message)
{
    zmq::message_t zmqMessage(message.size());
    memcpy(zmqMessage.data(), message.c_str(), message.size());

    const zmq::send_result_t &anOptional = end_work_.send(zmqMessage, zmq::send_flags::none);

    if (!anOptional.has_value())
    {
        std::cout << "Error sending end work message" << std::endl;
    }
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
    sender_.close();
    receiver_.close();
    end_work_.close();
    context_.close();
}
