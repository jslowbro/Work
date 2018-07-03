#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#define RESTRICTED 'X'
#include "wyjscie.h"
#include "struct.h"
#include <png.h>
//Macierz na konsole
void printMatrix(matrix_t matrix1) {
    for (int i = 0; i < matrix1->x; i++) {
        for (int j = 0; j < matrix1->y; j++) {
            if(matrix1->macierz[i*matrix1->y+j] != RESTRICTED) {
                printf("%c ", matrix1->macierz[i * matrix1->y + j]);
            }
        }
        printf("\n");
    }
}
//Funckja drukuje macierz do pliku nazwanego na podstawie unikatowej sygnatury i numeru generacji
void printMatrixToFile(matrix_t inputMatrix, int gen, int signature, char* dirname) {
    char filename[64];
    sprintf(filename, "%s%s%d%s%d%s",dirname,"/", signature, "_genNo.", gen, ".txt");
    FILE *file = fopen(filename,"w");
    fprintf(file,"%d %d\n", inputMatrix->x-2, inputMatrix->y-2);
    for (int i = 1; i < inputMatrix->x-1; i++) {
        for (int j = 1; j < inputMatrix->y-1; j++) {
            fprintf(file,"%c ", inputMatrix->macierz[i * inputMatrix->y + j]);
        }
        fprintf(file,"\n");
    }
    fclose(file);
}

void printMatrixToPNG(matrix_t inputMatrix, int gen, int signature, char*dirname)
{
    /* kod zostal wziety z materialow do przedmiotu JIMP2 z isod.ee.pw.edu.pl */
    int x,y;
    int width = inputMatrix->x;
    int height = inputMatrix->y;
    char filename[64];
    sprintf(filename, "%s%s%d%s%d%s",dirname,"/", signature, "_genNo.", gen, ".png");
    png_byte color_type = PNG_COLOR_TYPE_GRAY;
    png_structp png_ptr;
    png_infop info_ptr;
    png_byte bit_depth = 8;
    png_bytep * row_pointers;
    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (y=0; y<height; y++)
        row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * width);

    for (y=0; y<height; y++) {
    png_byte* row = row_pointers[y];
        for (x=0; x<width; x++) {
            row[x] = inputMatrix->macierz[(y)*(width)+x]=='0'||inputMatrix->macierz[(y)*(width)+x]=='X'? 0 : 255;
        }
    }

    FILE *fp = fopen(filename, "wb");
      if (!fp)
        printf("[write_png_file] File %s could not be opened for writing", filename);

      png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

      if (!png_ptr)
        printf("[write_png_file] png_create_write_struct failed");

      info_ptr = png_create_info_struct(png_ptr);
      if (!info_ptr)
        printf("[write_png_file] png_create_info_struct failed");

      if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during init_io");

      png_init_io(png_ptr, fp);

      if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during writing header");

      png_set_IHDR(png_ptr, info_ptr, width, height,
       bit_depth, color_type, PNG_INTERLACE_NONE,
       PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

      png_write_info(png_ptr, info_ptr);

      if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during writing bytes");

      png_write_image(png_ptr, row_pointers);

      if (setjmp(png_jmpbuf(png_ptr)))
        printf("[write_png_file] Error during end of write");

      png_write_end(png_ptr, NULL);

      for (y=0; y<height; y++)
        free(row_pointers[y]);
      free(row_pointers);
	png_destroy_write_struct(&png_ptr, &info_ptr);
      fclose(fp);
      /* koniec kodu wzietego z isod */
}
