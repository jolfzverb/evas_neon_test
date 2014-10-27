#include <arm_neon.h>
#include "map.h"
#define BUILD_NEON
#include "evas_blend_ops.h"

// 0
#define SCALE_USING_NEON
#undef SMOOTH
#undef COLMUL
#undef COLSAME
#undef COLBLACK
int neon_orig0(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#define SMOOTH
#undef COLMUL
#undef COLSAME
#undef COLBLACK
int neon_orig1(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#undef SMOOTH
#define COLMUL
#undef COLSAME
#undef COLBLACK
int neon_orig2(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#define SMOOTH
#define COLMUL
#undef COLSAME
#undef COLBLACK
int neon_orig3(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#undef SMOOTH
#undef COLMUL
#define COLSAME
#undef COLBLACK
int neon_orig4(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#define SMOOTH
#undef COLMUL
#define COLSAME
#undef COLBLACK
int neon_orig5(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#undef SMOOTH
#define COLMUL
#define COLSAME
#undef COLBLACK
int neon_orig6(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#define SMOOTH
#define COLMUL
#define COLSAME
#undef COLBLACK
int neon_orig7(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#undef SMOOTH
#undef COLMUL
#undef COLSAME
#define COLBLACK
int neon_orig8(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#define SMOOTH
#undef COLMUL
#undef COLSAME
#define COLBLACK
int neon_orig9(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#undef SMOOTH
#define COLMUL
#undef COLSAME
#define COLBLACK
int neon_orig10(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#define SMOOTH
#define COLMUL
#undef COLSAME
#define COLBLACK
int neon_orig11(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#undef SMOOTH
#undef COLMUL
#define COLSAME
#define COLBLACK
int neon_orig12(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#define SMOOTH
#undef COLMUL
#define COLSAME
#define COLBLACK
int neon_orig13(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#undef SMOOTH
#define COLMUL
#define COLSAME
#define COLBLACK
int neon_orig14(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
#define SMOOTH
#define COLMUL
#define COLSAME
#define COLBLACK
int neon_orig15(DATA32* _val1, DATA32* _val2, DATA32* _val3, DATA32* _val4, DATA32* _rv, DATA32* _ru, DATA32* result, int len, DATA32* _cv, DATA32 _c1, DATA32 _c2)
{
#include "orig_inc.c"
return 0;
}
