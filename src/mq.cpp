#include "app.hpp"

MQ::MQ(pcpp::DpdkDevice *dev) : Worker(dev) {
    assert(context = new zmq::context_t(1));
    assert(endpoint = new std::string("inproc://" + dev->getDeviceName()));
    std::clog << "mq: endpoint:" << *endpoint;
    assert(pull = new zmq::socket_t(*context, ZMQ_PULL));
    assert(push = new zmq::socket_t(*context, ZMQ_PUSH));
    pull->bind(*endpoint);
    std::clog << "\n";
}

MQ::~MQ() {}

MQ *MQ::test;

bool MQ::run(uint32_t coreId) {  //
    assert(Worker::run(coreId));
    while (!_stop) {
        //
        zmq::message_t request;
        if (pull->recv(request, zmq::recv_flags::dontwait)) {
            std::clog << "\tmq: " << *endpoint               //
                      << "\t\trecv:" << request.to_string()  //
                      << "\n";
        } else
            std::clog << "\n";

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return terminate();
}
