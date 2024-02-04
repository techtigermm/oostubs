//Source: https://github.com/LikeAnShadow/oostubs_changed/
//geklaut von https://stackoverflow.com/questions/2440385/how-to-find-the-physical-address-of-a-variable-from-user-space-in-linux

#ifndef VIRT_TO_PHYS_H
#define VIRT_TO_PHYS_H
#include "object/uint_templates.h"
uintptr_t virt_to_phys(uintptr_t virt_addr) {
    uintptr_t phys_addr = 0;
    int offset = ((uint64_t)virt_addr / 4096) *sizeof(uint64_t);

    return virt_addr + 0x103000;
}
#endif