#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int BLOCKSIZE = 512;

int main(int argc, char *argv[])
{
    //Check the command line args
    if (argc != 2)
    {
        printf("Usage : ./recover imagename \n");
        return 1;
    }
    //Open file
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Failed opening card.raw!\n");
        return 1;
    }
    else
    {
        printf("File card.raw is open for reading ...\n");
    }
    FILE *outfile = NULL;
    int iseof = 0;
    int isread = 0;
    int iswrite = 0;
    uint8_t buffer[BLOCKSIZE];
    int fileNum = -1;
    char outFileName[8];
    int blockNo = 0;
    printf("Reading blocks: ");

    // loop until the end of file
    while (iseof == 0)
    {
        // Reading a block of memory to the buffer. Checking for eof and errors
        isread = fread(buffer, sizeof(uint8_t), BLOCKSIZE, infile);
        if (isread == 0)
        {
            if (ferror(infile) != 0)
            {
                printf("Error reading file!\n");
                return 2;
            }
            else
            {
                iseof = feof(infile);
                if (iseof != 0)
                {
                    printf("End of file reached.\n");
                    if (outfile != NULL) // so the file is open
                    {
                        fclose(outfile);
                    }
                }
                else
                {
                    printf("Strange! not eof and not error but ...\n");
                    return 3;
                }
            }
        }

        // Checking current buffer for the key uint8_ts
        if (buffer[0] == 0xff  &&  buffer[1] == 0xd8  &&  buffer[2] == 0xff  && buffer[3] >= 0xe0  &&  buffer[3] <= 0xef)
        {
            if (fileNum >= 0) // We alredy are writing a file
            {
                fclose(outfile);
            }

            fileNum++; // incrementing the number of file
            sprintf(outFileName, "%03d.jpg", fileNum); // forming the filename
            outfile = fopen(outFileName, "w"); // opening the file for writing and checking for success
            if (outfile == NULL)
            {
                printf("Failed opening %3d.jpg for writing!\n", fileNum);
                return 4;
            }
            else
            {
                printf("\n\nFile %s is open for writing.\n\n", outFileName);
            }

            // Writing current block as the first one to the file
            iswrite = fwrite(buffer, sizeof(uint8_t), BLOCKSIZE, outfile);
            if (iswrite == 0)
            {
                printf("Error writing file %03d.jpg!\n", fileNum);
                return 5;
            }
        }
        else if (fileNum >= 0) // We alredy are writing a file
        {
            // Writing current block as the current one to the file
            iswrite = fwrite(buffer, sizeof(uint8_t), BLOCKSIZE, outfile);
            if (iswrite == 0)
            {
                printf("Error writing file %03d.jpg!\n", fileNum);
                return 5;
            }
        }
    }
    fclose(infile);
}
