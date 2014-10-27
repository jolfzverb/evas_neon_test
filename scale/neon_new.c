#include <arm_neon.h>
#include "scale.h"

int neon_new(DATA32* _p0, DATA32* _p1, DATA32* _p2, DATA32* _p3, DATA32* _ax, DATA32 _ay, DATA32* result, int len) {
  int ay = _ay;
  int i;
  DATA32* pbuf = result;
	    uint16x4_t ay_16x4;
	    uint16x4_t p0_16x4;
	    uint16x4_t p2_16x4;
	    uint16x8_t ax_16x8;
	    uint16x8_t p0_p2_16x8;
	    uint16x8_t p1_p3_16x8;
	    uint16x8_t x255_16x8;
	    uint32x2_t p0_p2_32x2;
	    uint32x2_t p1_p3_32x2;
	    uint32x2_t res_32x2;
	    uint8x8_t p0_p2_8x8;
	    uint8x8_t p1_p3_8x8;
	    uint8x8_t p2_8x8;
	    uint16x4_t temp_16x4;

	    ay_16x4 = vdup_n_u16(ay);
	    x255_16x8 = vdupq_n_u16(0xff);
  for(i = 0; i < len; i++) {
    DATA32 p0 = *_p0++;
    DATA32 p1 = *_p1++;
    DATA32 p2 = *_p2++;
    DATA32 p3 = *_p3++;
    int ax = *_ax++;
		if (p0 | p1 | p2 | p3)
		  {
		    ax_16x8 = vdupq_n_u16(ax);

		    p0_p2_32x2 = vset_lane_u32(p0, p0_p2_32x2, 0);
		    p0_p2_32x2 = vset_lane_u32(p2, p0_p2_32x2, 1);
		    p1_p3_32x2 = vset_lane_u32(p1, p1_p3_32x2, 0);
		    p1_p3_32x2 = vset_lane_u32(p3, p1_p3_32x2, 1);

		    p0_p2_8x8 = vreinterpret_u8_u32(p0_p2_32x2);
		    p1_p3_8x8 = vreinterpret_u8_u32(p1_p3_32x2);
		    p1_p3_16x8 = vmovl_u8(p1_p3_8x8);
		    p0_p2_16x8 = vmovl_u8(p0_p2_8x8);

		    p1_p3_16x8 = vsubq_u16(p1_p3_16x8, p0_p2_16x8);
		    p1_p3_16x8 = vmulq_u16(p1_p3_16x8, ax_16x8);
		    p1_p3_16x8 = vshrq_n_u16(p1_p3_16x8, 8);
		    p1_p3_16x8 = vaddq_u16(p1_p3_16x8, p0_p2_16x8);
		    p1_p3_16x8 = vandq_u16(p1_p3_16x8, x255_16x8);

		    p0_16x4 = vget_low_u16(p1_p3_16x8);
		    p2_16x4 = vget_high_u16(p1_p3_16x8);

		    p2_16x4 = vsub_u16(p2_16x4, p0_16x4);
		    p2_16x4 = vmul_u16(p2_16x4, ay_16x4);
		    p2_16x4 = vshr_n_u16(p2_16x4, 8);
		    p2_16x4 = vadd_u16(p2_16x4, p0_16x4);

		    p1_p3_16x8 = vcombine_u16(temp_16x4, p2_16x4);
		    p2_8x8 = vmovn_u16(p1_p3_16x8);
		    res_32x2 = vreinterpret_u32_u8(p2_8x8);
		    vst1_lane_u32(pbuf++, res_32x2, 1);
		  }
		else
		  *pbuf++ = p0;

  }
	return 0;
}
