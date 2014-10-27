#define pld(addr, off)

#define UNROLL2(op...) op op
#define UNROLL4(op...) UNROLL2(op) UNROLL2(op)
#define UNROLL8(op...) UNROLL4(op) UNROLL4(op)
#define UNROLL16(op...) UNROLL8(op) UNROLL8(op)

#define UNROLL8_PLD_WHILE(start, size, end, op)         \
    pld(start, 0);                                      \
    end = start + (size & ~7);                          \
    while (start < end)                                 \
        {                                               \
            pld(start, 32);                             \
            UNROLL8(op);                                \
        }                                               \
    end += (size & 7);                                  \
    pld(start, 32);                                     \
    while (start <  end)                                \
        {                                               \
        op;                                             \
        }

