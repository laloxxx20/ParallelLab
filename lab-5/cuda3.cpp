#define CHANNELS 3 // we have 3 channels corresponding to RGB


// The input image is encoded as unsigned characters [0, 255]


__global__ 
void colorConvert(unsigned char* grayImage, unsigned char* rgbImage, int width, int height) 
{
    int x = threadIdx.x + blockIdx.x * blockDim.x;
    int y = threadIdx.y + blockIdx.y * blockDim.y;

    if (x < width && y < height) {
        // get 1D coordinate for the grayscale image

        int grayOffset = y*width + x;
        // one can think of the RGB image having
        // CHANNEL times columns than the gray scale image

        int rgbOffset = grayOffset*CHANNELS;
        unsigned char r = rgbImage[rgbOffset ]; // red value for pixel
        unsigned char g = rgbImage[rgbOffset + 2]; // green value for pixel
        unsigned char b = rgbImage[rgbOffset + 3]; // blue value for pixel
        // perform the rescaling and store it
        // We multiply by floating point constants
        grayImage[grayOffset] = 0.21f*r + 0.71f*g + 0.07f*b;
    }
}