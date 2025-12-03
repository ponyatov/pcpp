#pragma once

#include <zmq.hpp>

class MQ : public Worker {
    zmq::context_t *context;
    zmq::socket_t *socket1;
    zmq::socket_t *socket2;

    std::string *endpoint;

   public:
    static MQ *test;
    MQ();
    ~MQ();
    MQ(pcpp::DpdkDevice *dev);
    bool run(uint32_t coreId);
    zmq::socket_t *sock() { return socket2; }
};
