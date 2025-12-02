#include "pcpp.hpp"

bool Group::run(uint32_t coreId) {  //
    _coreId = coreId;
    std::clog << "group:" << g->name      //
              << " core:" << getCoreId()  //
              << "\n";
    for (auto s : g->sensors) {  //
        std::clog << "\tsensor:" << s->name << "\n";
    }
    while (!_stop) {  //
        packet.computeCalculateFields();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return true;
}

// bool Send::run(uint32_t coreId) {  //
// pcpp::EthLayer Group::eth_layer(sendMac, recvMac, PCPP_ETHERTYPE_IP);
//     packet.addLayer(&eth_layer);
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
