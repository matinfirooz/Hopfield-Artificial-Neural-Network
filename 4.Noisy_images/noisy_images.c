#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WIDTH 8       
#define HEIGHT 8      
#define NUM_IMAGES 10 
#define NOISE_LEVEL 0.05
#define NUM_NOISY_IMAGES 8 

// Function to add noise by flipping random pixels
void add_noise(char *image_bits, int width, int height, float noise_level) {
    int num_pixels = width * height; 
    int num_noisy_pixels = (int)(num_pixels * noise_level);
    
    
    for (int i = 0; i < num_noisy_pixels; i++) {
        int rand_index = rand() % num_pixels; 
        image_bits[rand_index / 8] ^= (1 << (rand_index % 8)); 
    }
}

// Function to save a noisy image as an XBM file
void save_noisy_image(char *image_bits, int width, int height, int image_index, int noise_index) {
    char filename[50]; 
    sprintf(filename, "noisy_%d_%d.xbm", image_index + 1, noise_index + 1);
    
    FILE *file = fopen(filename, "w"); 
    if (file) {
        fprintf(file, "#define im_width %d\n", width); 
        fprintf(file, "#define im_height %d\n", height); 
        fprintf(file, "static char noisy_%d_%d_bits[] = {\n", image_index + 1, noise_index + 1);
        
        
        for (int i = 0; i < (width * height) / 8; i++) {
            fprintf(file, "0x%02x", image_bits[i] & 0xFF);
            if (i < (width * height) / 8 - 1) {
                fprintf(file, ",");
            }
        }
        
        fprintf(file, "\n};\n"); 
        fclose(file); 
    }
}

int main() {
    srand(time(NULL));
    
    for (int i = 0; i < NUM_IMAGES; i++) { 
        char image_bits[WIDTH * HEIGHT / 8]; 
        
         // Load image data from XBM file
        char filename[20];
        sprintf(filename, "%d.xbm", i + 1); 
        FILE *file = fopen(filename, "r"); 
        if (file) {
            char buffer[100];
            int byte_index = 0;
            while (fgets(buffer, sizeof(buffer), file)) { 
                if (buffer[0] == '0' && buffer[1] == 'x') { 
                    sscanf(buffer, "%hhx", &image_bits[byte_index]); 
                    byte_index++;
                }
            }
            fclose(file); 
        }
        
        // Generate noisy variations of the image
        for (int j = 0; j < NUM_NOISY_IMAGES; j++) { 
            char noisy_image_bits[WIDTH * HEIGHT / 8]; 
            memcpy(noisy_image_bits, image_bits, WIDTH * HEIGHT / 8); 
            add_noise(noisy_image_bits, WIDTH, HEIGHT, NOISE_LEVEL); 
            save_noisy_image(noisy_image_bits, WIDTH, HEIGHT, i, j);
        }
    }
    
    return 0;
}


