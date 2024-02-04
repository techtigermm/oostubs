#ifndef OOSTUBS_STRCMP_H
#define OOSTUBS_STRCMP_H
int strcmpEqu(char* str1, char* str2) {
    for(;str1 !=nullptr && str2 != nullptr; str1++, str2++) {
        if(*str1 == '\0' && *str2 == '\0') return 1;
        if(*str1 == '\0' || *str2 == '\0') return 0;
        if(*str1 != *str2) return 0;
    }
    return 1;
}
#endif //OOSTUBS_STRCMP_H