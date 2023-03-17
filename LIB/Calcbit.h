#ifndef CALCBIT_H
#define CALCBIT_H

#define setbit(reg, bit_no) ((reg) |= (1 << bit_no))
#define clearbit(reg, bit_no) ((reg) &= ~(1 << bit_no))
#define getbit(reg, bit_no) (((reg) & (1 << bit_no)) >> bit_no)
// #define getbit(reg, bit_no) ((reg >> bit_no) & 1)
#define togglebit(reg, bit_no) ((reg) ^= (1 << bit_no))

/* fixes compatability issues */
#define SETBIT(x, y) setbit((x), (y))
#define CLEARBIT(x, y) clearbit((x), (y))
#define GETBIT(x, y) getbit((x), (y))
#define TOGGLEBIT(x, y) togglebit((x), (y))

#endif