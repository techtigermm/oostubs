//Source: https://github.com/LikeAnShadow/oostubs_changed/
#include "driver.h"
#include "machine/io_port.h"
#include "machine/pci.h"
#include "object/virttophys.h"
void RTL8139::setBus(int b) {
    bus = b;
}
void RTL8139::setSlot(int s) {
    slot = s;
}
void RTL8139::setFunction(int f) {
    function = f;
}
void RTL8139::setConnected(bool c) {
    isConnected = c;
}
void RTL8139::setBufferPtr(uintptr_t bpt){
    bufferPtr = bpt;
}
void RTL8139::setTxBufferPtr(uint8_t *ptr){
    tx_buffer = ptr;
}

int RTL8139::getBus() {
    return bus;
}
int RTL8139::getSlot() {
    return slot;
}
int RTL8139::getFunction() {
    return function;
}
bool RTL8139::getConnected() {
    return isConnected;
}
uintptr_t RTL8139::getBufferPtr() {
    return bufferPtr;
}

uint32_t RTL8139::getMac_p1() {
    return mac_p1;
}
uint16_t RTL8139::getMac_p2() {
    return mac_p2;
}

char *RTL8139::displayFullMac(){
    int m1 = mac_p1;
    int m2 = mac_p2;
}

uint32_t RTL8139::getIoAddr() {
    return ioaddr;
}


// Quelle: https://wiki.osdev.org/RTL8139, angepasst
void RTL8139::initialize(uintptr_t ptr){
    //Setze Buffer
    setBufferPtr(ptr);
    //Schreibe die IO-Adresse auf
    ioaddr = pciConfigReadLong(getBus(), getSlot(), getFunction(), 0x10) - 1;
    //Lese die zwei Teile der MAC-Adresse ein (6Byte (4Byte | 2Byte))
    mac_p1 = inl(ioaddr + 0x1);
    mac_p2 = inl(ioaddr + 0x4);
    //Schalte das Gerät durch setzen von 0x00 auf das CONFIG_1 Register an
    outb(ioaddr + 0x52, 0x0);
    //Software-Reset um sicherzugehen, dass sich kein Müll in den Buffern befindet
    outb(ioaddr + 0x37, 0x10);
    //Checke das RST Bit (Wenn != 0 ist das Gerät noch am resetten)
    while((inb(ioaddr + 0x37) & 0x10) != 0) {}
    //Setze den RECV-Buffer(unser ptr, der Bereits übernommen wurde)
    outl(ioaddr + 0x30, *getBufferPtr());
    //Setze das Interrupt Mask Register (IMR) auf 0x0005 um zu Empfangen und Senden
    outw(ioaddr + 0x3C, 0x0005);
    //Konfigurieren des RECV-Buffers (https://wiki.osdev.org/RTL8139#Configuring_receive_buffer_.28RCR.29)
    outl(ioaddr + 0x44, 0xf | (1 << 7));
    //Senden und Empfangsbits auf High, TX und RX möglich
    outb(ioaddr + 0x37, 0x0C);
}

void RTL8139::sendPacket(const uint8_t *data, int size) {
    for(int i = 0; i < size; i++) {
        tx_buffer[i] = data[i];
    }
    outl(ioaddr + 0x10, (uint64_t)virt_to_phys((uintptr_t)tx_buffer));
    outl(ioaddr + 0x20, size);
}

/*void rtl8139_handler(uint8_t isr, uint64_t error, uint64_t irq) {
	uint16_t status = inw(ioaddr + 0x3e);
	outw(io_base + 0x3E, 0x05);
	if(status & TOK) {
		// Sent
	}
	if (status & ROK) {
		// Received
		receive_packet();
	}
}*/