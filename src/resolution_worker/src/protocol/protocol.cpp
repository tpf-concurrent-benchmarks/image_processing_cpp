#include <constants.h>
#include "protocol.h"

Protocol::Protocol(const std::string &brokerFromFormat, const std::string &brokerFromSize, const std::string &pushPort,
                   const std::string &pullPort)
{
    context_ = zmq::context_t(3);
    sender_ = zmq::socket_t(context_, ZMQ_PUSH);
    receiver_ = zmq::socket_t(context_, ZMQ_PULL);
    end_work_ = zmq::socket_t(context_, ZMQ_SUB);
    sender_.connect("tcp://" + brokerFromSize + ":" + pushPort);
    receiver_.connect("tcp://" + brokerFromFormat + ":" + pullPort);
    end_work_.connect("tcp://manager:" + Constants::END_WORK_PORT);
    end_work_.setsockopt(ZMQ_SUBSCRIBE, "", 0);
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

std::string Protocol::receive()
{
    zmq::pollitem_t items[] = {
            {static_cast<void *>(receiver_), 0, ZMQ_POLLIN, 0},
            {static_cast<void *>(end_work_), 0, ZMQ_POLLIN, 0}};
    zmq::poll(&items[0], 2, -1);

    if (items[0].revents & ZMQ_POLLIN)
    {
        zmq::message_t message;
        const zmq::recv_result_t &anOptional = receiver_.recv(message);
        if (!anOptional.has_value())
        {
            return "Error message";
        }
        return std::string(static_cast<char *>(message.data()), message.size());
    }
    else if (items[1].revents & ZMQ_POLLIN)
    {
        zmq::message_t message;
        const zmq::recv_result_t &anOptional = end_work_.recv(message);
        if (!anOptional.has_value())
        {
            return "Error message";
        }
        return std::string(static_cast<char *>(message.data()), message.size());
    }
    else
    {
        return "Error message";
    }
}

void Protocol::close()
{
    sender_.close();
    receiver_.close();
    end_work_.close();
    context_.close();
}
