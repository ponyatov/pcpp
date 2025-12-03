#pragma once

#include "app.hpp"
#include "libc.hpp"
#include "group.hpp"

class MQ : public Worker {
    zmq::context_t *context;
    std::string *endpoint;
    zmq::socket_t *pull;
    zmq::socket_t *push;

   public:
    MQ(pcpp::DpdkDevice* dev, GROUP* g);
    ~MQ();
    bool run(uint32_t coreId);
    void send(std::string message);
};
