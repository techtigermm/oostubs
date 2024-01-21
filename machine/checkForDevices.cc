//Source: https://github.com/LikeAnShadow/oostubs_changed/
#include "../object/uint_templates.h"
#include "pci.h"
#include "machine/checkForDevices.h"
uint32_t checkFullDevice(int bus, int slot){
    uint16_t vendorID = pciCheckVendor(bus, slot, 0);
    if(vendorID == 0xFFFF) return 0xFFFFFFFF;
    uint16_t deviceID = pciCheckDevice(bus, slot, 0);
    uint32_t fullDeviceID = ((uint32_t)vendorID << 16) | (uint32_t)deviceID;
    return fullDeviceID;
}