typedef unsigned int DATA32;

int neon_orig(DATA32* _p0, DATA32* _p1, DATA32* _p2, DATA32* _p3, DATA32* _ax, DATA32 _ay, DATA32* result, int len);
int c_orig(DATA32* _p0, DATA32* _p1, DATA32* _p2, DATA32* _p3, DATA32* _ax, DATA32 _ay, DATA32* result, int len);
int neon_new(DATA32* _p0, DATA32* _p1, DATA32* _p2, DATA32* _p3, DATA32* _ax, DATA32 _ay, DATA32* result, int len);
