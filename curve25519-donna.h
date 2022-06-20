#include <stdint.h>

extern "C" {
    typedef uint8_t u8;
    int curve25519_donna(u8 *mypublic, const u8 *secret, const u8 *basepoint);
}
