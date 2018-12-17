
#include "bmp.h"

read_err from_bmp(FILE* in, image_t* const img_input){
    bmp_header_t bmp_header;
    if (fread(&bmp_header, sizeof(bmp_header_t),1, in) != 1) return READ_INVALID_HEADER;
    if (bmp_header.biBitCount != 24) return READ_INVALID_BITS;
    img_input->height = bmp_header.biHeight;
    img_input->width  = bmp_header.biWidth;
    img_input->data = (pixel_t*)malloc(img_input->height * img_input->width * sizeof(pixel_t));
    fseek(in, bmp_header.bOffBits,SEEK_SET);
    for(int i=0;i<img_input->height;i++){
        fread(img_input->data + ((img_input->height - i - 1)*img_input->width),sizeof(pixel_t),img_input->width,in);
        fseek(in,img_input->width%4,SEEK_CUR);
    }
    return READ_OK;
}

image_t image_rotate(image_t const source){
    image_t img_rotate;
	uint32_t i, j;
	img_rotate.height = source.width;
	img_rotate.width = source.height;
	img_rotate.data = (pixel_t*)malloc(img_rotate.width * img_rotate.height * sizeof(pixel_t));
	for(int i=0;i<source.height;i++)
        for(int j=0;j<source.width;j++){
          //printf("%d %d\n",i,j);
          *(img_rotate.data + j*img_rotate.width + img_rotate.width - i-1) = *(source.data + i*source.width + j);
        }
    return img_rotate;
}
write_err to_bmp(FILE* out, image_t const* img){
    uint32_t i;
	char* str = "000";
	for (i = 0; i < img->height; ++i) {
		if (fwrite(img->data + (img->height - i - 1) * img->width, sizeof(pixel_t), img->width, out) != img->width) return WRITE_ERROR;
		fflush(out);
		fwrite(str, img->width % 4, 1, out);
		fflush(out);
	}
	return WRITE_OK;
}
void copy_header(FILE* in, FILE* out, int tmp) {
	bmp_header_t bmp_header;
	uint32_t var;
	fseek(in, 0, SEEK_SET);
	fread(&bmp_header, sizeof(bmp_header_t), 1, in);
	fflush(in);
	var = bmp_header.biHeight;
	if (tmp) {
		bmp_header.biHeight = bmp_header.biWidth;
		bmp_header.biWidth = var;
	}
	bmp_header.bfileSize = bmp_header.bOffBits + 3 * bmp_header.biHeight * bmp_header.biWidth + bmp_header.biHeight * (bmp_header.biWidth % 4);

	fwrite(&bmp_header, sizeof(bmp_header_t), 1, out);
	fflush(out);
	fseek(out, bmp_header.bOffBits, SEEK_SET);
}
