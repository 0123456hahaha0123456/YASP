#ifndef bmp.h
#define bmp.h
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 2)
typedef struct bmp_header{
 uint16_t bfType;
 uint32_t bfileSize;
 uint32_t bfReserved;
 uint32_t bOffBits; // after how many bits is begin of file
 uint32_t biSize;
 uint32_t biWidth; // chieu rong anh
 uint32_t biHeight;// chieu dai anh

 uint16_t biPlanes;
 uint16_t biBitCount;// how many bit in pixel

 uint32_t biCompression;
 uint32_t biSizeImage;
 uint32_t biXPelsPerMeter;
 uint32_t biYPelsPerMeter;
 uint32_t biClrUsed;
 uint32_t biClrImportant;
} bmp_header_t;
#pragma pack(pop)

typedef struct pixel_t {
    unsigned char b,g,r;
} pixel_t;

typedef struct {
    uint64_t width,height;
    struct pixel_t* data;
} image_t ;

typedef enum {
    READ_OK = 0,
    READ_INVALID_HEADER,
    READ_INVALID_BITS
} read_err;

typedef enum {
	WRITE_OK = 0,
	WRITE_ERROR
} write_err;

extern read_err from_bmp(FILE* in, image_t* const img_input);
extern image_t image_rotate(image_t const source);
extern write_err to_bmp(FILE* out, image_t const* img);
extern void copy_header(FILE* in, FILE* out,int tmp);
#endif
