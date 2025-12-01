#pragma once

#define MBUF_POOL_SZ (8192-1)

#include <DpdkDevice.h>
#include <DpdkDeviceList.h>
#include <SystemUtils.h>

#include <cassert>
#include <iostream>

extern int main(int argc, char* argv[]);
extern void arg(int argc, char* argv);

extern void init(int argc, char* argv[]);
