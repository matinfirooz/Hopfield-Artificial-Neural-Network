#include <stdio.h>
#include <math.h>  
#include "1.xbm"
#include "2.xbm"
#include "3.xbm"
#include "4.xbm"
#include "5.xbm"
#include "6.xbm"
#include "7.xbm"
#include "8.xbm"
#include "9.xbm"
#include "10.xbm"

#define NEURONS 64  

int weights[NEURONS][NEURONS] = {0};  
int recognize[NEURONS];  
int patterns[10][NEURONS];  
int max_sum = 0;  

// Update the state of a single neuron
void update_neuron(int x, int *new_recognize) {
    int sum = 0;
    for (int i = 0; i < NEURONS; i++) {
        sum += weights[i][x] * recognize[i];  
    }
    if (sum > max_sum) {
        max_sum = sum;  
    }
    new_recognize[x] = (sum >= 0) ? 1 : 0;  
}

// Convert image data to pattern format
void insert_img(int *pattern, char *x_bits) {
    for (int i = 0; i < NEURONS / 8; i++) {
        for (int j = 0; j < 8; j++) {
            pattern[i * 8 + j] = (x_bits[i] & (1 << (7 - j))) ? 1 : 0;
        }
    }
}

// Train the network using Hebbian learning
void train(int *pattern) {
    for (int i = 0; i < NEURONS; i++) {
        for (int j = 0; j < NEURONS; j++) {
            if (i != j) {
                weights[i][j] += (2 * pattern[i] - 1) * (2 * pattern[j] - 1);
            }
        }
    }
}

// Print the current recognition pattern
void print_pat(int *pattern) {
    for (int i = 0; i < NEURONS; i++) {
        if (i % 8 == 0) {
            printf("\n");
        }
        printf("[%d]", pattern[i]);  
    }
    printf("\n");
}

// Update all neurons for a fixed number of iterations
void update_all() {
    int new_recognize[NEURONS];
    for (int i = 0; i < 10; i++) {  
        for (int j = 0; j < NEURONS; j++) {
            update_neuron(j, new_recognize);  
        }
        for (int k = 0; k < NEURONS; k++) {
            recognize[k] = new_recognize[k];  
        }
        printf("Recognition pattern after update cycle %d:\n", i + 1);
        print_pat(recognize);  
    }
}

// Calculate accuracy between two patterns
double calculate_accuracy(int *pattern1, int *pattern2) {
    int matches = 0;
    for (int i = 0; i < NEURONS; i++) {
        if (pattern1[i] == pattern2[i]) {
            matches++;  
        }
    }
    return (double)matches / NEURONS;  
}

int main() {
    // Load XBM image data into patterns
    char *x_bits[] = {_1_bits, _2_bits, _3_bits, _4_bits, _5_bits, _6_bits, _7_bits, _8_bits, _9_bits, _10_bits};  
    for (int i = 0; i < 10; i++) {
        insert_img(patterns[i], x_bits[i]);  
        train(patterns[i]);  
    }
    update_all();  
    printf("Maximum sum encountered: %d\n", max_sum);  

    // Compute required bits to represent max_sum
    int bits_required = (int)ceil(log2(max_sum + 1));
    printf("Number of bits required to represent the maximum sum: %d\n", bits_required);

    return 0;
}
