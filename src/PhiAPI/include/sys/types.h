#ifndef PhiOS_types
#define PhiOS_types

//typedef unsigned long long          p_uint64;
typedef unsigned int                p_uint32;
typedef unsigned short              p_uint16;
typedef unsigned char               p_uint8;
//typedef signed   long long          p_sint64;
typedef signed   int                p_sint32;
typedef signed   short              p_sint16;
typedef signed   char               p_sint8;

//typedef unsigned long long          p_u64int;
typedef unsigned int                p_u32int;
typedef unsigned short              p_u16int;
typedef unsigned char               p_u8int;
//typedef signed   long long          p_s64int;
typedef signed   int                p_s32int;
typedef signed   short              p_s16int;
typedef signed   char               p_s8int;

//typedef const unsigned long long    p_cuint64;
typedef const unsigned int          p_cuint32;
typedef const unsigned short        p_cuint16;
typedef const unsigned char         p_cuint8;
//typedef const signed   long long    p_csint64;
typedef const signed   int          p_csint32;
typedef const signed   short        p_csint16;
typedef const signed   char         p_csint8;

//typedef const unsigned long long    p_cu64int;
typedef const unsigned int          p_cu32int;
typedef const unsigned short        p_cu16int;
typedef const unsigned char         p_cu8int;
//typedef const signed   long long    p_cs64int;
typedef const signed   int          p_cs32int;
typedef const signed   short        p_cs16int;
typedef const signed   char         p_cs8int;

typedef char                        p_bool;

#define p_true 1
#define p_false 0
#define P_NULL 0x00000000

/*
 * p_size_t should be always on 64bits, but first time must be implemented
 * __udivdi3 and __divdi3
 */
#ifdef PhiOS32
typedef p_uint32 p_size_t;
#else
typedef p_uint64 p_size_t;
#endif

#endif

