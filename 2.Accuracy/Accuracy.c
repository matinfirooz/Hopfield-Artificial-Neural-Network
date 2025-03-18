#include <stdio.h>
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

#define NEURONS 64 // Number of neurons

// Weight matrix and pattern arrays
int weights[NEURONS][NEURONS] = {0};
int recognize[NEURONS]; 
int patterns[10][NEURONS]; 

// Function to update a single neuron based on its weighted sum
void update_neuron(int x, int *new_recognize) {
    int sum = 0;
    for (int i = 0; i < NEURONS; i++) {
        sum += weights[i][x] * recognize[i];
    }
    new_recognize[x] = (sum >= 0) ? 1 : 0; // Activation function
}

// Function to insert an image pattern into the network
void insert_img(int *pattern, char *x_bits) {
    for (int i = 0; i < NEURONS / 8; i++) {
        for (int j = 0; j < 8; j++) {
            pattern[i * 8 + j] = (x_bits[i] & (1 << (7 - j))) ? 1 : 0;
        }
    }
}

// Function to train the network with a given pattern using Hebbian learning
void train(int *pattern) {
    for (int i = 0; i < NEURONS; i++) {
        for (int j = 0; j < NEURONS; j++) {
            if (i != j) {
                weights[i][j] += (2 * pattern[i] - 1) * (2 * pattern[j] - 1);
            }
        }
    }
}

// Function to print a stored pattern
void print_pat(int *pattern) {
    for (int i = 0; i < NEURONS; i++) {
        if (i % 8 == 0) {
            printf("\n");
        }
        printf("[%d]", pattern[i]);
    }
    printf("\n");
}

// Function to update all neurons in the network iteratively perform 10 cycle
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

// Function to calculate the accuracy of pattern recognition
double calculate_accuracy(int *pattern1, int *pattern2) {
    int matches = 0;
    for (int i = 0; i < NEURONS; i++) {
        if (pattern1[i] == pattern2[i]) {
            matches++;
        }
    }
    return (double)matches / NEURONS * 100; 
}

// Main function to simulate the Hopfield network
int main() {
    // Load patterns into the network
    insert_img(patterns[0], _1_bits);
    insert_img(patterns[1], _2_bits);
    insert_img(patterns[2], _3_bits);
    insert_img(patterns[3], _4_bits);
    insert_img(patterns[4], _5_bits);
    insert_img(patterns[5], _6_bits);
    insert_img(patterns[6], _7_bits);
    insert_img(patterns[7], _8_bits);
    insert_img(patterns[8], _9_bits);
    insert_img(patterns[9], _10_bits);
    insert_img(recognize, _10_bits);

    // Train the network using the loaded patterns
    for (int i = 0; i < 10; i++) {
        train(patterns[i]);
    }

    // Print the initial recognition pattern
    printf("Initial recognize pattern:\n");
    print_pat(recognize);

    // Update all neurons iteratively
    update_all();

    // Print the final recognition pattern after updates
    printf("Updated recognize pattern:\n");
    print_pat(recognize);

    // Calculate and print accuracy by comparing with pattern 10
    double accuracy = calculate_accuracy(recognize, patterns[9]);  
    printf("Accuracy: %.2f%%\n", accuracy);

    getchar();

    return 0;
}
