#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Reads in a bitmap and a message and encodes the message into a new bitmap
int main(int argc, char *argv[]) {
    if (argc < 4 || argc > 4) {
        printf("Error: Argument count");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Error: Opening base bitmap failed");
        return 1;
    }

    FILE* output = fopen(argv[2], "w");
    if (!output) {
        printf("Error: Output file creation failed");
        fclose(fp);
        return 1;
    }

    char *message = argv[3];
    if (!message) {
        printf("Error: Message storage failed");
        fclose(fp);
        fclose(output);
        return 1;
    }

    // Offset for determining starting pixel
    fseek(fp, 10, SEEK_SET);
    int pixelStart = getc(fp);

    // Store header bytes into array
    char header[54];
    for (int i = 0; i < 54; i++) {
        fseek(fp, i, SEEK_SET);
        header[i] = getc(fp);
        fputc(header[i], output);
    }

    // Extract width and height from header array
    int width = *(int *) &header[18];
    int height = *(int *) &header[22];

    printf("Pixils start at: %d\n", pixelStart);
    printf("Width of image: %d\n", width);
    printf("Height of image: %d\n", height);

    // Iterates through each RGBa value in image
    fseek(fp, pixelStart, SEEK_SET);
    int posHeight = abs(height);
    int charIndex = 0;
    int bitIndex = 0;
    int nullIndex = 0;
    // Iterates through each RGBa value, so we have to multiply by 4 to get through all the pixels in the image
    for (int index = 0; index < posHeight * width * 4; index++) {
        int color = getc(fp);
        // Skip the alpha value in each pixel
        if (index % 4 != 3 && charIndex <= (int) strlen(message)) {
            // Retreive least significant bit (LSB)
            char LSB = (message[charIndex] >> bitIndex) & 1;
            // Encode LSB into color byte and write to output bmp
            color = (color >> 1) << 1;
            color = color | LSB;
            fputc(color, output);
            // Index logic
            bitIndex++;
            if (bitIndex > 7) {
                bitIndex = 0;
                charIndex++;
            }
        // Encode a null byte to end the secret message
        } else if (charIndex >= (int) strlen(message) && nullIndex < 8) {
            // Clear LSB of color byte to encode '\0'
            color = (color >> 1) << 1;
            fputc(color, output);
            nullIndex++;
        // Copy the color to the new bmp
        } else {
            fputc(color, output);
        }	
    }

    fclose(fp);
    fclose(output);

    return 0;
}
