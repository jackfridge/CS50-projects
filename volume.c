// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor ("r" is for read)
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // "w" is for write mode
    FILE *output = fopen(argv[2], "w");
    
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Convert factor argument to a float value (allow for decimal values, example 0.5)
    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];

    fread(&header, HEADER_SIZE, 1, input);
    fwrite(&header, HEADER_SIZE, 1, output);
    
    // TODO: Read samples from input file and write updated data to output file
    // 16 bit sample = 2 bytes per sample
    int16_t buffer;
    
    // As long as fread returns a value, keep copying data
    while (fread(&buffer, 2, 1, input))
    {
        buffer = buffer * factor;
        fwrite(&buffer, 2, 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);

    printf("File successfully made.\n");
    return 0;
}
