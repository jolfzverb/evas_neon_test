/* some useful C macros */

#define MUL4_256(a, r, g, b, c) \
 ( (((((c) >> 8) & 0xff0000) * (a)) & 0xff000000) + \
   (((((c) & 0xff0000) * (r)) >> 8) & 0xff0000) + \
   (((((c) & 0xff00) * (g)) >> 8) & 0xff00) + \
   ((((c) & 0xff) * (b)) >> 8) )

#define MUL3_256(r, g, b, c) \
 ( (((((c) & 0xff0000) * (r)) >> 8) & 0xff0000) + \
   (((((c) & 0xff00) * (g)) >> 8) & 0xff00) + \
   ((((c) & 0xff) * (b)) >> 8) )

#define MUL_256(a, c) \
 ( (((((c) >> 8) & 0x00ff00ff) * (a)) & 0xff00ff00) + \
   (((((c) & 0x00ff00ff) * (a)) >> 8) & 0x00ff00ff) )

#define MUL4_SYM(x, y) \
 ( ((((((x) >> 16) & 0xff00) * (((y) >> 16) & 0xff00)) + 0xff0000) & 0xff000000) + \
   ((((((x) >> 8) & 0xff00) * (((y) >> 16) & 0xff)) + 0xff00) & 0xff0000) + \
   ((((((x) & 0xff00) * ((y) & 0xff00)) + 0xff0000) >> 16) & 0xff00) + \
   (((((x) & 0xff) * ((y) & 0xff)) + 0xff) >> 8) )

#define MUL3_SYM(x, y) \
 ( ((((((x) >> 8) & 0xff00) * (((y) >> 16) & 0xff)) + 0xff00) & 0xff0000) + \
   ((((((x) & 0xff00) * ((y) & 0xff00)) + 0xff0000) >> 16) & 0xff00) + \
   (((((x) & 0xff) * ((y) & 0xff)) + 0xff) >> 8) )

#define MUL_SYM(a, x) \
 ( (((((x) >> 8) & 0x00ff00ff) * (a) + 0xff00ff) & 0xff00ff00) + \
   (((((x) & 0x00ff00ff) * (a) + 0xff00ff) >> 8) & 0x00ff00ff) )

#define MUL_A_256(a, c) \
 ( ((((c) >> 8) & 0x00ff0000) * (a)) & 0xff000000 )

#define MUL_A_SYM(a, c) \
 ( (((((c) >> 8) & 0x00ff0000) * (a)) + 0x00ff0000) & 0xff000000 )

#define INTERP_256(a, c0, c1) \
 ( (((((((c0) >> 8) & 0xff00ff) - (((c1) >> 8) & 0xff00ff)) * (a)) \
   + ((c1) & 0xff00ff00)) & 0xff00ff00) + \
   (((((((c0) & 0xff00ff) - ((c1) & 0xff00ff)) * (a)) >> 8) \
   + ((c1) & 0xff00ff)) & 0xff00ff) )

#define INTERP_RGB_256(a, c0, c1) \
 ( (((((((c0) >> 8) & 0xff) - (((c1) >> 8) & 0xff)) * (a)) \
   + ((c1) & 0xff00)) & 0xff00) + \
   (((((((c0) & 0xff00ff) - ((c1) & 0xff00ff)) * (a)) >> 8) \
   + ((c1) & 0xff00ff)) & 0xff00ff) )

#define INTERP_A_256(a, c0, c1) \
 ( (((((((c0) >> 8) & 0xff0000) - (((c1) >> 8) & 0xff0000)) * (a)) \
   + ((c1) & 0xff000000)) & 0xff000000) )


#ifdef BUILD_NEON_INLINE
#define FPU_NEON \
	__asm__ __volatile__(".fpu neon \n\t");

/* copy reg1 to reg2 */
#define VMOV_R2R_NEON(reg1, reg2) \
	__asm__ __volatile__("vmov " #reg1 ", " #reg2 " \n\t" ::: #reg1);

/* copy 32bit value to lower bits of register reg */
#define VMOV_M2R_NEON(reg, value) \
	__asm__ __volatile__("vmov.32 " #reg "[0], %[val] \n\t" :: [val] "r" (value) : #reg); 

/* save 32bit value from lower 64 bits of register regq to memory location */
/* pointed to by pointer, using 64bit register regd as temporary location */
#define VMOV_R2M_NEON(regq, regd, pointer) \
	__asm__ __volatile__("vqmovn.u16 " #regd ", " #regq " \n\t" \
			     "vst1.32 {" #regd "[0]}, [%[p]] \n\t" :: [p] "r" (pointer) : #regd, "memory");

/* spread constant imm in register reg */
#define VMOV_I2R_NEON(reg, imm) \
	__asm__ __volatile__("vmov.i16 " #reg ", " #imm " \n\t" ::: #reg);

/* spread value in register reg */
#define VDUP_NEON(reg, value) \
	__asm__ __volatile__("vdup.16 " #reg ", %[val] \n\t" :: [val] "r" (value) : #reg); 

/* interleave contents of reg1 and reg2 */
#define VZIP_NEON(reg1, reg2) \
	__asm__ __volatile__("vzip.8 " #reg1 ", " #reg2 " \n\t" ::: #reg1 , #reg2);

/* swap contents of two registers */
#define VSWP_NEON(reg1, reg2) \
	__asm__ __volatile__("vswp " #reg1 ", " #reg2 " \n\t" ::: #reg1 , #reg2);

/* set register to zero */
#define VEOR_NEON(reg) \
	__asm__ __volatile__("veor " #reg ", " #reg ", " #reg " \n\t" ::: #reg);

/* do interpolation of every channel RGBA, result is contained in regy */
#define INTERP_256_NEON(rega, regx, regy, reg255) \
	__asm__ __volatile__("vsub.i16 " #regx ", " #regx ", " #regy " \n\t" \
			     "vmul.u16 " #regx ", " #regx ", " #rega " \n\t" \
			     "vsri.16 " #regx ", " #regx ", #8 \n\t" \
			     "vadd.i16 " #regx ", " #regx ", " #regy " \n\t" \
			     "vand " #regy ", " #regx ", " #reg255 " \n\t" \
			     ::: #regx, #regy );

/* multiply every channel of regx and regy */
#define MUL4_SYM_NEON(regx, regy, reg255) \
	__asm__ __volatile__("vmul.u16 " #regx ", " #regx ", " #regy " \n\t" \
			     "vadd.i16 " #regx ", " #regx ", " #reg255 " \n\t" \
			     "vsri.16 " #regx ", " #regx ", #8 \n\t" \
			     "vand " #regx ", " #regx ", " #reg255 " \n\t" \
			     ::: #regx );

#endif
