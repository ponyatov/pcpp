#include "pcpp.hpp"

bool Group::run(uint32_t coreId) {  //
    _coreId = coreId;
    std::clog << "group:" << g->name      //
              << " core:" << getCoreId()  //
              << "\n";
    packet = new pcpp::Packet();
    eth_layer = new pcpp::EthLayer(sendMac, recvMac, PCPP_ETHERTYPE_IP);
    packet->addLayer(eth_layer);
    sends = 0;
    while (!_stop) {
        // std::clog << "group:" << g->name << " sends:" << ++sends << "\n";

        // sensors loop
        for (auto s : g->sensors) {
            // std::clog << "\tsensor:" << s->name;
            packet->removeAllLayersAfter(eth_layer);
            ipv4_layer = new pcpp::IPv4Layer(s->src.ip, s->dst.ip);
            packet->addLayer(ipv4_layer);
            frame.src = htobe16(s->src.port);
            frame.dst = htobe16(s->dst.port);
            frame.length = htobe16(s->packetSize + 8);  // with UDP
            frame.crc = 0;                              // ignore
            // std::clog                                      //
            //     << " " << s->src.ip << ':' << s->src.port  //
            //     << " -> " << s->dst.ip << ':' << s->dst.port;
            // std::clog << "\n";

            // fragmentation loop
            ipId++;
            for (uint offset = 0; offset < s->packetSize; offset += Dev::MTU) {
                // compute frame payload size
                if (offset + Dev::MTU > s->packetSize)
                    fragment_size = s->packetSize % Dev::MTU;
                else
                    fragment_size = Dev::MTU;
                // copy sensor data to
                memcpy(frame.data, &s->start[offset], fragment_size);
                // std::clog << "\t\tframe:" << offset << '/' << fragment_size;
                // frame payload
                if (!offset) {                                  // first frame
                    frame.length = htobe16(s->packetSize + 8);  // with UDP
                    payload = new pcpp::PayloadLayer(           //
                        (uint8_t *)&frame, fragment_size + 8);  //
                } else {                                        // 1+ frame
                    payload = new pcpp::PayloadLayer(           //
                        frame.data, fragment_size);
                }
                packet->addLayer(payload);
                // fragmentation
                packet->computeCalculateFields();
                auto ip_hdr = ipv4_layer->getIPv4Header();      // fix IP header
                ip_hdr->ipId = htobe16(ipId);                   // fragmens id
                ip_hdr->timeToLive = 5;                         // min TTL
                ip_hdr->protocol = pcpp::PACKETPP_IPPROTO_UDP;  //
                //
                ip_hdr->fragmentOffset =
                    htobe16(offset + (offset ? 8 : 0) / sizeof(uint16_t));
                if (offset + Dev::MTU < s->packetSize)
                    ip_hdr->fragmentOffset |= MF_flag;
                else
                    ip_hdr->fragmentOffset &= ~MF_flag;
                //
                pcpp::ScalarBuffer<uint16_t> ip_scalar = {
                    (uint16_t *)ip_hdr,  //
                    (size_t)(ip_hdr->internetHeaderLength * 4)};
                assert(ip_scalar.len == 20);
                ip_hdr->headerChecksum = 0;
                ip_hdr->headerChecksum =
                    htobe16(pcpp::computeChecksum(&ip_scalar, 1));
                //
                dev->sendPacket(*packet);
                // std::clog << "\n";
            }
        }
        // std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
    return true;
}
