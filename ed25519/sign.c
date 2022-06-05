#include "ed25519.h"
#include "ge.h"
#include "sc.h"
#include "../blake2b/blake2.h"

void ed25519_sign(unsigned char *signature, const unsigned char *message, size_t message_len, const unsigned char *public_key, const unsigned char *private_key) {
  blake2b_state hash;
  unsigned char hram[64];
  unsigned char r[64];
  ge_p3 R;


  blake2b_init(&hash, 32);
  blake2b_update(&hash, private_key + 32, 32);
  blake2b_update(&hash, message, message_len);
  blake2b_final(&hash, r, 32);

  sc_reduce(r);
  ge_scalarmult_base(&R, r);
  ge_p3_tobytes(signature, &R);

  blake2b_init(&hash, 32);
  blake2b_update(&hash, signature, 32);
  blake2b_update(&hash, public_key, 32);
  blake2b_update(&hash, message, message_len);
  blake2b_final(&hash, hram, 32);

  sc_reduce(hram);
  sc_muladd(signature + 32, hram, private_key, r);
}
