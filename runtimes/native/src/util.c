#include "util.h"
#include <stdlib.h>
#include <stdio.h>

#if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#    define W4_BIG_ENDIAN
#endif

void* xmalloc(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fputs("Allocation failed.\n", stderr);
        abort();
    }
    return ptr;
}

void* xrealloc(void* ptr, size_t size) {
    ptr = realloc(ptr, size);
    if (ptr == NULL) {
        fputs("Allocation failed.\n", stderr);
        abort();
    }
    return ptr;
}

uint16_t bswap16(uint16_t x) {
    return ((( x  >> 8 ) & 0xffu ) | (( x  & 0xffu ) << 8 ));
}

uint32_t bswap32(uint32_t x) {
    return ((( x & 0xff000000u ) >> 24 ) |
            (( x & 0x00ff0000u ) >> 8  ) |
            (( x & 0x0000ff00u ) << 8  ) |
            (( x & 0x000000ffu ) << 24 ));
}

uint16_t w4_read16LE (const uint16_t* ptr) {
#ifdef W4_BIG_ENDIAN
    return bswap16(*ptr);
#else
    return *ptr;
#endif
}

uint32_t w4_read32LE (const uint32_t* ptr) {
#ifdef W4_BIG_ENDIAN
    return bswap32(*ptr);
#else
    return *ptr;
#endif
}

double w4_readf64LE (const uint64_t* ptr) {
    union {
        uint64_t u;
        double d;
    } u;
#ifdef W4_BIG_ENDIAN
    u.u = bswap32(*ptr);
#else
    u.u = *ptr;
#endif
    return u.d;
}

void w4_write16LE (uint16_t* ptr, uint16_t value) {
#ifdef W4_BIG_ENDIAN
    *ptr = bswap16(value);
#else
    *ptr = value;
#endif
}

void w4_write32LE (uint32_t* ptr, uint32_t value) {
#ifdef W4_BIG_ENDIAN
    *ptr = bswap32(value);
#else
    *ptr = value;
#endif
}
