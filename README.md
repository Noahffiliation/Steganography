# Steganography
The word steganography means "concealed writing." Steganography has been used for centuries to transmit secret messages. Using steganography, the secret message is hidden in some transportation medium such as an image, book, or music. The secret message can only be retrieved by a receiver that knows how to decode the message. For this project you will create a bitmap image file (BMP) encoder. The encoder will store the bits of a secret message in the least significant bits of each RGB color byte of a BMP file.

The resulting encoded image file will appear to be mostly unaltered. This is because the least significant bit will not always be changed and when it is, the change will be imperceptible. For example a color value made up of RED 255, GREEN 255, and BLUE 255 (white) may become the color made up of RED 254, GREEN 254, and BLUE 254 (mostly white). The difference between white and mostly white is visually imperceptible.

## Build/Installation
```
gcc -std=c11 -Wall -Wextra -Werror -pedantic -o encode encode.c
```

## Usage
- Argument 1: path to an input file. The input file has the following characteristics:
    - Uncompressed BMP file
    - 32 bit pixel size
- Argument 2: path to an output file
    - File may or may not exist, if it does exist it will be overwritten
- Argument 3: text string containing secret message

Example:
```
./encode sheldon.bmp enc.bmp "Secret Message"
```

- The encoded image can be decoded [here](https://cse.taylor.edu/~dstanley/cos232/decoder.php)
