#include "machine/network.h"
/*void IPPacket::setHeaderLength(uint8_t headerl) {
    ihl = 3;
}
void IPPacket::setToS(uint8_t type){
    tos = 0;
}
void IPPacket::setTotalLength(uint16_t length){
    total_length = (32*getHeaderLength()) + length;
}
void IPPacket::setIdentification(uint16_t){
    identification=0;
}
void IPPacket::setFlags(uint8_t fl){
    flags=0;
}
void IPPacket::setFragmentOffset(uint16_t fo){
    fragment_offset = 0;
}
void IPPacket::setTTL(uint8_t t){
    ttl = t;
}
void IPPacket::setProtocol(uint8_t p){
    protocol = p;
}
*/
void IPPacket::calcCheckSum() {

}
uint8_t IPPacket::getHeaderLength() {
    return 5;
}