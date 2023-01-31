#define ZP_MATRIX_Moonlander( \
    k00, k01, k02, k03, k04, k05, k06, \
    k10, k11, k12, k13, k14, k15, k16, \
    k20, k21, k22, k23, k24, k25, k26, \
    k30, k31, k32, k33, k34, k35,      \
    k40, k41, k42, k43, k44,           \
    k53, \
    k50, k51, k52, \
    \
    k60, k61, k62, k63, k64, k65, k66, \
    k70, k71, k72, k73, k74, k75, k76, \
    k80, k81, k82, k83, k84, k85, k86, \
    k91, k92, k93, k94, k95, k96, \
    ka2, ka3, ka4, ka5, ka6, \
    kb3,\
    kb4, kb5, kb6 \
) \
{ \
    /* Left half */             \
    k00, k10, k20, k30, k40,    \
    k01, k11, k21, k31, k41,    \
    k02, k12, k22, k32, k42,    \
    k03, k13, k23, k33, k43,    \
    k04, k14, k24, k34, k44,    \
    k05, k15, k25, k35,         \
    k06, k16, k26,              \
                                \
    /* Left thumb cluster */    \
    k50, k51, k52,              \
    k53,                        \
                                \
    /* Right half */            \
    k66, k76, k86, k96, ka6,    \
    k65, k75, k85, k95, ka5,    \
    k64, k74, k84, k94, ka4,    \
    k63, k73, k83, k93, ka3,    \
    k62, k72, k82, k92, ka2,    \
    k61, k71, k81, k91,         \
    k60, k70, k80,              \
                                \
    /* Right thumb cluster */   \
    kb4, kb5, kb6,              \
    kb3                         \
}

// Moonlander zones
#define MY_L_MIN  0
#define MY_L_MAX  32
#define MY_LT_MIN 32
#define MY_LT_MAX 36
#define MY_R_MIN  36
#define MY_R_MAX  68
#define MY_RT_MIN 68
#define MY_RT_MAX 72

#define ZP_ZONES_NUM 4

#define ZP_ZONE_LEFT 0
#define ZP_ZONE_RIGHT 3
#define ZP_ZONE_LEFT_THUMB 1
#define ZP_ZONE_RIGHT_THUMB 2

#define ZP_ZONE_0_MIN MY_L_MIN
#define ZP_ZONE_0_MAX MY_L_MAX

#define ZP_ZONE_1_MIN MY_LT_MIN
#define ZP_ZONE_1_MAX MY_LT_MAX

#define ZP_ZONE_2_MIN MY_RT_MIN
#define ZP_ZONE_2_MAX MY_RT_MAX

#define ZP_ZONE_3_MIN MY_R_MIN
#define ZP_ZONE_3_MAX MY_R_MAX

#define ZP_LAYER_LAYOUT 1
#define ZP_LAYER_PICTURE 2
#define ZP_LAYER_HOST 3

#define ZP_BACKGROUND_VAL 128

