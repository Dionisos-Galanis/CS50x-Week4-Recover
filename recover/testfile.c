#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    FILE *outfile = fopen("mytest.bin", "w");
    uint8_t k;
    for (int i = 0; i < 256; i++)
    {
        k = (uint8_t) i;
        fwrite(&k, sizeof(uint8_t), 1, outfile);
    }
    fclose(outfile);

    FILE *infile = fopen("mytest.bin", "r");
    uint8_t buffer[256];
    fread(buffer, sizeof(uint8_t), 256, infile);

    for (int i = 1; i < 256; i++)
    {
        printf("%3d ", buffer[i]);
    }
    printf("\n");
}