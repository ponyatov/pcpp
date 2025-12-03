#include "app.hpp"

MQ::MQ(pcpp::DpdkDevice *dev) : Worker(dev) {
    assert(context = new zmq::context_t(1));
    assert(endpoint = new std::string("inproc://" + dev->getDeviceName()));
    std::clog << "mq: endpoint:" << *endpoint;
    assert(socket1 = new zmq::socket_t(*context, zmq::socket_type::pair));
    assert(socket2 = new zmq::socket_t(*context, zmq::socket_type::pair));
    socket1.bind(endpoint);
    std::clog << "\n";
}

MQ::~MQ() {}

MQ *MQ::test;

bool MQ::run(uint32_t coreId) {  //
    assert(Worker::run(coreId));
    while (!_stop) {
        std::clog << "mq: " << *endpoint;
        //
        zmq::message_t request;
        auto t = socket1->recv(request, zmq::recv_flags::none);
        std::cout << " recv:" << request.to_string();
        //
        std::clog << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return terminate();
}
