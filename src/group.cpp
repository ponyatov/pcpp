#include "pcpp.hpp"

bool Group::run(uint32_t coreId) {        //
    std::clog << "group:" << g->name      //
              << " core:" << getCoreId()  //
              << "\n";
    return false;
}
