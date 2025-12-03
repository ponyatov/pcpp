#include "app.hpp"

MQ::MQ(pcpp::DpdkDevice* dev, GROUP* g) : Worker(dev) {
    context = new zmq::context_t(1);
    endpoint = new std::string("inproc://" + g->name);
    pull = new zmq::socket_t(*context, ZMQ_PULL);
    push = new zmq::socket_t(*context, ZMQ_PUSH);
    assert(context && endpoint && pull && push);
    std::clog << "mq: endpoint:" << *endpoint;
    pull->bind(*endpoint);
    push->connect(*endpoint);
    std::clog << "\n";
}

MQ::~MQ() {
    push->close();
    delete push;
    pull->close();
    delete pull;
    delete endpoint;
    context->close();
    delete context;
}

bool MQ::run(uint32_t coreId) {  //
    assert(Worker::run(coreId));
    while (!_stop) {
        //
        zmq::message_t msg;
        if (pull->recv(msg, zmq::recv_flags::dontwait)) {
            std::string message(static_cast<char*>(msg.data()), msg.size());
            std::clog << "\tmq: " << *endpoint              //
                      << " message:<" << message << ">\n";  //
        }

        std::this_thread::sleep_for(std::chrono::microseconds(333));
    }
    return terminate();
}

void MQ::send(std::string message) {  //
    zmq::message_t msg(message.data(), message.size());
    push->send(msg, zmq::send_flags::dontwait);
}
