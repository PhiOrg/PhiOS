#ifndef PhiOS_types
#define PhiOS_types

typedef unsigned long long          p_uint64;
typedef unsigned int                p_uint32;
typedef unsigned short              p_uint16;
typedef unsigned char               p_uint8;
typedef          long long          p_sint64;
typedef          int                p_sint32;
typedef          short              p_sint16;
typedef          char               p_sint8;

typedef unsigned long long          p_u64int;
typedef unsigned int                p_u32int;
typedef unsigned short              p_u16int;
typedef unsigned char               p_u8int;
typedef          long long          p_s64int;
typedef          int                p_s32int;
typedef          short              p_s16int;
typedef          char               p_s8int;

typedef const unsigned long long    p_cuint64;
typedef const unsigned int          p_cuint32;
typedef const unsigned short        p_cuint16;
typedef const unsigned char         p_cuint8;
typedef const          long long    p_csint64;
typedef const          int          p_csint32;
typedef const          short        p_csint16;
typedef const          char         p_csint8;

typedef const unsigned long long    p_cu64int;
typedef const unsigned int          p_cu32int;
typedef const unsigned short        p_cu16int;
typedef const unsigned char         p_cu8int;
typedef const          long long    p_cs64int;
typedef const          int          p_cs32int;
typedef const          short        p_cs16int;
typedef const          char         p_cs8int;

typedef char                        p_bool;

#define p_true 1
#define p_false 0
#define P_NULL 0x00000000

#endif

