#pragma once

#include <zmq.hpp>

class MQ : public Worker {
    zmq::context_t *context;
    zmq::socket_t *pull;
    zmq::socket_t *push;

    std::string *endpoint;

   public:
    static MQ *test;
    MQ();
    ~MQ();
    MQ(pcpp::DpdkDevice *dev);
    bool run(uint32_t coreId);
};
