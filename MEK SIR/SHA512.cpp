#include <stdlib.h>
#include <stdio.h>

#define ROTR(x, n) ((x >> n) | (x << (64 - n))) 
#define Ch(e, f, g) (((e) & (f)) ^ ((~(e)) & (g)))
#define Maj(a, b, c) (((a) & (b)) ^ ((a) & (c)) ^ ((b) & (c)))
#define BigSO(x) (ROTR(x, 14) ^ ROTR(x, 18) ^ ROTR(x, 41))
#define BigS1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ (x >> 10))
#define SmallSO(x) (ROTR(x, 1) ^ ROTR(x, 8) ^ (x >> 7))

#define ll  long long

ll init_value[8] = {
    0x6a09e667f3bcc908ll, 0xbb67ae8584caa73bll, 0x3c6ef372fe94f82bll,
    0xa54ff53a5f1d36f1ll, 0x510e527fade682d1ll, 0x9b05688c2b3e6c1fll,
    0x1f83d9abfb41bd6bll, 0x5be0cd19137e2179ll
};

int main() {
    for (int i = 0; i < 8; i++) {
        printf("init_value[%d] = %llx\n", i, init_value[i]);
    }
    return 0;
}
