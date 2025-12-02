#include "pcpp.hpp"

bool Group::run(uint32_t coreId) {  //
    _coreId = coreId;
    std::clog << "group:" << g->name      //
              << " core:" << getCoreId()  //
              << "\n";
    packet = new pcpp::Packet();
    eth_layer = new pcpp::EthLayer(sendMac, recvMac, PCPP_ETHERTYPE_IP);
    packet->addLayer(eth_layer);
    while (!_stop) {
        std::clog << "group:" << g->name << "\n";
        // frame = 0;

        // sensors loop
        for (auto s : g->sensors) {
            std::clog << "\tsensor:" << s->name;
            ipv4_layer = new pcpp::IPv4Layer(s->src.ip, s->dst.ip);
            packet->addLayer(ipv4_layer);
            frame.src = htobe16(s->src.port);
            frame.dst = htobe16(s->dst.port);
            std::clog                                      //
                << " " << s->src.ip << ':' << s->src.port  //
                << " -> " << s->dst.ip << ':' << s->dst.port;
            std::clog << "\n";

            // fragmentation loop
            uint fragment_size = Dev::MTU;
            for (uint offset = 0; offset < s->packetSize;) {
                // compute frame payload size
                if (offset + Dev::MTU <= s->packetSize)
                    fragment_size = Dev::MTU;
                else
                    fragment_size = s->packetSize % Dev::MTU;
                // copy sensor data to
                memcpy(frame.data, &s->start[offset], fragment_size);
                offset += fragment_size;
                std::clog << "\t\tframe:" << offset  //
                          << '/' << fragment_size << "\n";
                //
                packet->computeCalculateFields();
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return true;
}

// bool Send::run(uint32_t coreId) {  //
//
//
//     pcpp::MBufRawPacket* mbufArr[64] = {};
//     for (int i = 0; i < 64; i++) {  //
//         auto raw = packet.getRawPacket();
//         auto mbuf = new pcpp::MBufRawPacket();
//         mbuf->initFromRawPacket(raw, dev);
//         mbufArr[i] = mbuf;
//     }
//     while (!_stop) {  //
//         // dev->sendPacket(packet);
//         dev->sendPackets(mbufArr, 64, 0);
//         // std::this_thread::sleep_for(std::chrono::nanoseconds(1));
//     }
//     return true;
// }
