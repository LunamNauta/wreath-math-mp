#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

//TODO: Rename variables to be in wm namespace

#ifndef WM_MP_FULL_T
#define WM_MP_FULL_T uint64_t
#endif
#ifndef WM_MP_HALF_T
#define WM_MP_HALF_T uint32_t
#endif
#ifndef WM_MP_SHIFT
#define WM_MP_SHIFT 2
#endif

typedef WM_MP_FULL_T mp_full_t;
typedef WM_MP_HALF_T mp_half_t;
const mp_half_t WM_MP_MASK = ((mp_half_t)1 << WM_MP_SHIFT)-1;

mp_half_t mpn_add_1(mp_half_t* out, const mp_half_t* lhs, size_t n, mp_half_t rhs){
    mp_half_t carry = 0;
    size_t a = 0;
    for (; a < n; a++){
        carry += lhs[a];
        out[a] = carry & WM_MP_MASK; 
        carry >>= WM_MP_SHIFT;
    }
    for (; a < n; a++) out[a] = lhs[a];
    return carry;
}
mp_half_t mpn_add_n(mp_half_t* out, const mp_half_t* lhs, const mp_half_t* rhs, size_t n){
    mp_half_t carry = 0;
    for (size_t a = 0; a < n; a++){
        carry += lhs[a] + rhs[a];
        out[a] = carry & WM_MP_MASK;
        carry >>= WM_MP_SHIFT;
    }
    return carry;
}
mp_half_t mpn_add(mp_half_t* out, const mp_half_t* lhs, size_t ln, const mp_half_t* rhs, size_t rn){
    mp_half_t carry = 0;
    size_t a = 0;
    for (; a < rn; a++){
        carry += lhs[a] + rhs[a];
        out[a] = carry & WM_MP_MASK;
        carry >>= WM_MP_SHIFT;
    }
    for (; a < ln; a++){
        carry += lhs[a];
        out[a] = carry & WM_MP_MASK;
        carry >>= WM_MP_SHIFT;
    }
    return carry;
}
