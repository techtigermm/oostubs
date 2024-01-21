#include "../object/uint_templates.h"

uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint32_t pciConfigReadLong(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);
uint16_t pciCheckVendor(uint8_t bus, uint8_t slot, uint8_t function);
uint16_t pciCheckDevice(uint8_t bus, uint8_t slot, uint8_t function);
uint16_t pciGetHeaderType(uint8_t bus, uint8_t slot, uint8_t function);