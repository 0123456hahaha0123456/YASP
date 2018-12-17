#include "bmp.h"

int main(int args, char** argv)
{
    FILE *picture_in;
    FILE *picture_out;
    image_t img_read;
    image_t img_write;
    read_err err;
    char filename_in[256]= "D:\\Russia\\thirdsemester\\YASP\\Lab5\\pic.bmp";
    char filename_out[256] = "D:\\Russia\\thirdsemester\\YASP\\Lab5\\rotated.bmp";

    picture_in = fopen(filename_in,"rb");

    if (picture_in == NULL){
        perror("Wrong file");
        return 0;
    }

    bmp_header_t bmp_header;
    err = from_bmp(picture_in,&img_read);

    if (err == READ_OK){
        img_write = image_rotate(img_read);
		picture_out = fopen(filename_out, "wb");
		copy_header(picture_in,picture_out,1);
		to_bmp(picture_out,&img_write);
		fflush(picture_out);
		fclose(picture_out);
		printf("Your picture has rotated already!\n");
    }
    else printf("File couldn't be read");
    fclose(picture_in);
    free(img_write.data);
    return 0;
}
