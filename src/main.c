#include <stdlib.h>
#include <stdint.h>

#ifndef WMATH_MP_FULL_T
#define WMATH_MP_FULL_T uint64_t
#endif
#ifndef WMATH_MP_HALF_T
#define WMATH_MP_HALF_T uint32_t
#endif
#ifndef WMATH_MP_SHIFT
#define WMATH_MP_SHIFT 2
#endif

typedef WMATH_MP_FULL_T wmath_mp_full_t;
typedef WMATH_MP_HALF_T wmath_mp_half_t;
const wmath_mp_half_t WMATH_MP_MASK = ((wmath_mp_half_t)1 << WMATH_MP_SHIFT)-1;

wmath_mp_half_t wmath_mpn_add_1(wmath_mp_half_t* out, const wmath_mp_half_t* lhs, size_t n, wmath_mp_half_t rhs){
    wmath_mp_half_t carry = 0;
    size_t a = 0;
    for (; carry && a < n; a++){
        carry += lhs[a] + (a==0?rhs:0);
        out[a] = carry & WMATH_MP_MASK; 
        carry >>= WMATH_MP_SHIFT;
    }
    for (; a < n; a++) out[a] = lhs[a];
    return carry;
}
wmath_mp_half_t wmath_mpn_add_n(wmath_mp_half_t* out, const wmath_mp_half_t* lhs, const wmath_mp_half_t* rhs, size_t n){
    wmath_mp_half_t carry = 0;
    for (size_t a = 0; a < n; a++){
        carry += lhs[a] + rhs[a];
        out[a] = carry & WMATH_MP_MASK;
        carry >>= WMATH_MP_SHIFT;
    }
    return carry;
}
wmath_mp_half_t wmath_mpn_add(wmath_mp_half_t* out, const wmath_mp_half_t* lhs, size_t ln, const wmath_mp_half_t* rhs, size_t rn){
    wmath_mp_half_t carry = 0;
    size_t a = 0;
    for (; a < rn; a++){
        carry += lhs[a] + rhs[a];
        out[a] = carry & WMATH_MP_MASK;
        carry >>= WMATH_MP_SHIFT;
    }
    for (; carry && a < ln; a++){
        carry += lhs[a];
        out[a] = carry & WMATH_MP_MASK;
        carry >>= WMATH_MP_SHIFT;
    }
    for (; a < ln; a++) out[a] = lhs[a];
    return carry;
}

wmath_mp_half_t wmath_mpn_sub_1(wmath_mp_half_t* out, const wmath_mp_half_t* lhs, size_t n, wmath_mp_half_t rhs){
    wmath_mp_half_t borrow = 0;
    size_t a = 0;
    for (; borrow && a < n; a++){
        borrow = lhs[a] - (a==0?rhs:0) - borrow;
        out[a] = borrow & WMATH_MP_MASK; 
        borrow >>= WMATH_MP_SHIFT;
        borrow &= 1;
    }
    for (; a < n; a++) out[a] = lhs[a];
    return borrow;
}
wmath_mp_half_t wmath_mpn_sub_n(wmath_mp_half_t* out, const wmath_mp_half_t* lhs, const wmath_mp_half_t* rhs, size_t n){
    wmath_mp_half_t borrow = 0;
    for (size_t a = 0; a < n; a++){
        borrow = lhs[a] - rhs[a] - borrow;
        out[a] = borrow & WMATH_MP_MASK;
        borrow >>= WMATH_MP_SHIFT;
        borrow &= 1;
    }
    return borrow;
}
wmath_mp_half_t wmath_mpn_sub(wmath_mp_half_t* out, const wmath_mp_half_t* lhs, size_t ln, const wmath_mp_half_t* rhs, size_t rn){
    wmath_mp_half_t borrow = 0;
    size_t a = 0;
    for (; a < rn; a++){
        borrow = lhs[a] - rhs[a] - borrow;
        out[a] = borrow & WMATH_MP_MASK;
        borrow >>= WMATH_MP_SHIFT;
        borrow &= 1;
    }
    for (; borrow && a < ln; a++){
        borrow = lhs[a] - borrow;
        out[a] = borrow & WMATH_MP_MASK;
        borrow >>= WMATH_MP_SHIFT;
        borrow &= 1;
    }
    for (; a < ln; a++) out[a] = lhs[a];
    return borrow;
}

int main(){

}
