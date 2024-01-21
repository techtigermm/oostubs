//Source: https://github.com/LikeAnShadow/oostubs_changed
#ifndef OOSTUBS_NETWORK_H
#define OOSTUBS_NETWORK_H
#include "object/uint_templates.h"
class IPPacket {
    //Version des Pakets (IPv4 | IPv6) 4bit
    uint8_t version_ihl;
    //Type of Service (Priorisierung) 8bit
    uint8_t tos;
    //Länge des gesamten Pakets (inklusive Header) 16bit
    uint16_t total_length;
    // Mit flags und fragment_offset (Reassembly von fragmentierten (aufgeteilten) Datenpaketen) 16bit
    uint16_t identification;
    /*
    3bit (Zusammenfassen mit fragment_offset)
    Gibt Fragmentierung an.
    Bit 0: immer 0, reserviert
    Bit 1: Dont Fragment(1, wenn nicht fragmentiert)
    Bit 2: More Fragments(1, wenn mehr weitere Fragmente folgen)
    */
    uint16_t flags_frag_off;
    // TimeToLive, gibt die Anzahl an Hops an, bis das Paket verschmissen wird 8bit
    uint8_t ttl;
    //Gibt das Verwendete Protokoll des Pakets an. Liste: https://www.iana.org/assignments/protocol-numbers/protocol-numbers.xhtml 8bit
    uint8_t protocol;
    //Checksumme des Pakets 16bit
    uint16_t checksum;
    protected:
    IPPacket(uint8_t version, uint8_t tos, uint16_t length,
    uint16_t identification,uint8_t flags,
    uint16_t fragment_offset, uint8_t ttl,
    uint8_t protocol): tos(tos),total_length(length + 32 * getHeaderLength()), identification(identification), ttl(ttl), protocol(protocol) {
        version_ihl = version << 4 | getHeaderLength();
        flags_frag_off = flags << 13 | fragment_offset;
        calcCheckSum();
    }
    public:
    uint16_t getTotalLength() {
        return total_length;
    }
/*
    void setHeaderLength(uint8_t headerl);
    void setToS(uint8_t type);
    void setTotalLength(uint16_t length);
    void setIdentification(uint16_t);
    void setFlags(uint8_t fl);
    void setFragmentOffset(uint16_t fo);
    void setTTL(uint8_t t);
    void setProtocol(uint8_t);
    */
    void calcCheckSum();

    uint8_t getHeaderLength();
};

class IPv4Packet: public IPPacket {
    //IP-Adresse des Senders 32bit
    uint32_t source;
    //IP-Adresse des Empfängers 32bit
    uint32_t dest;
    protected:
    IPv4Packet(uint32_t source, uint32_t dest,uint16_t length, uint8_t protocol, uint8_t ttl = 64, uint8_t tos = 0, uint16_t identification = 0, uint8_t flags = 0, uint16_t fragment_offset = 0):IPPacket(4, tos, length + sizeof(IPv4Packet), identification, flags, fragment_offset, ttl, protocol){}
   /*
    void setSource(uint32_t src);
    void setDest(uint32_t dest);
    */
};
//Noch nicht konfiguriert
class IPv6Packet: public IPPacket {
    public:
    //IPPacket():version(6){}
};

#endif