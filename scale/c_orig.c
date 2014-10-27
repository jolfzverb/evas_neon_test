#include "scale.h"
#include "evas_blend_ops.h"

int c_orig(DATA32* _p0, DATA32* _p1, DATA32* _p2, DATA32* _p3, DATA32* _ax, DATA32 _ay, DATA32* result, int len) {
  int ay = _ay;
  int i;
  DATA32* pbuf = result;
  for(i = 0; i < len; i++) {

    DATA32 p0 = *_p0++;
    DATA32 p1 = *_p1++;
    DATA32 p2 = *_p2++;
    DATA32 p3 = *_p3++;
    int ax = *_ax++;

		if (p0 | p1)
		  p0 = INTERP_256(ax, p1, p0);
		if (p2 | p3)
		  p2 = INTERP_256(ax, p3, p2);
		if (p0 | p2)
		  p0 = INTERP_256(ay, p2, p0);
		*pbuf++ = p0;
  }
  return 0;
}
