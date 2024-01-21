//Source: https://github.com/LikeAnShadow/oostubs_changed/
#ifndef OOSTUBS_RTL8139_DRIV_H
#define OOSTUBS_RTL8139_DRIV_H
#include "object/uint_templates.h"
#include "machine/network.h"
class RTL8139 {
private:
    int bus;
    int slot;
    int function;
    uint32_t ioaddr;
    bool isConnected = false;
    uintptr_t bufferPtr = nullptr;
    uint32_t mac_p1;
    uint16_t mac_p2;
    uint8_t *tx_buffer;

    uint32_t ipv4;

    void setBufferPtr(uintptr_t bpt);
    char *displayFullMac();
public: 
    RTL8139(): isConnected(false){}
    int getBus();
    int getSlot();
    int getFunction();
    bool getConnected();
    uintptr_t getBufferPtr();
    uint32_t getMac_p1();
    uint16_t getMac_p2();
    uint32_t getIoAddr();
    uint32_t getIpv4();
    void setConnected(bool c);
    void setBus(int b);
    void setSlot(int s);
    void setFunction(int f);
    void initialize(uintptr_t ptr);
    void setIpv4(uint32_t ip);
    void sendPacket(const uint8_t *data, int size);
    void setTxBufferPtr(uint8_t *ptr);

};
#endif