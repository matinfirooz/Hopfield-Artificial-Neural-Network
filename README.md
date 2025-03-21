# Artificial Neural Network 

This repository contains code and documentation for the second exercise in the "Bio-Inspired Design" course (Semester 2024-2025, SBU,Iran). 

The goal of this exercise is to implement and work with different types of artificial neural networks, focusing on Hopfield networks.
The exercise involves modifying code, evaluating performance, and conducting experiments with noisy image datasets.

## Exercise Overview

The objective of this exercise is to work with neural networks that act as content-based memory, specifically implementing Hopfield networks. 

The following tasks are part of this exercise:

1. **Modify Code to Work with Provided Dataset**: 
   - You will receive a dataset that needs to be used with the provided base code.
   - Modify the code so it works with the dataset you receive. 

2. **Calculate Network Accuracy**:
   - Add code to compute the accuracy of the neural network based on the dataset.
   - The accuracy metric should be chosen and calculated according to the dataset provided.

3. **Determine a Fixed Bit Width for Neural Network Calculations**:
   - Adjust the neural network calculations to ensure the fixed bit width does not cause overflow.
   - Ensure that the neural network’s operations use an appropriate bit width for the calculations, particularly for multiply-accumulate (MAC) operations.

4. **Add Noise to Image Data**:
   - Using a set of images, generate noisy images by modifying a certain percentage of pixels (e.g., 5% of total pixels).
   - These noisy images will be used for training and testing the neural network.

5. **Dataset Information**:
   - The dataset provided includes 10 images, each with 80 variations of noisy images.
   - The images will be altered with random noise, and each pixel will be modified by a certain percentage (e.g., 5%).

## Requirements

- Python 3.x
- Required libraries (e.g., numpy, matplotlib) for neural network implementation and image processing.

## Steps to Complete the Exercise

1. **Code Modification**:
   - Modify the base code to ensure it works with the dataset you received.
   - Ensure all functions work for the specific dataset and provide output that matches expectations.

2. **Accuracy Calculation**:
   - Implement code to compute and display the accuracy of the neural network for the given dataset.
   - You can choose the accuracy metric (e.g., percentage of correct predictions).

3. **Bit Width Determination**:
   - Run the code with the current bit width and check for any overflow in the neural network's calculations.
   - If necessary, adjust the bit width and ensure that the neural network can run efficiently without overflow.

4. **Noisy Image Generation**:
   - Modify the image data by randomly changing a set percentage (e.g., 5%) of the pixels.
   - Replace these pixels with random values and use the modified images for training and testing.


## Deliverables

- Modified code that works with the dataset.
- A report detailing:
  - Code changes made.
  - Accuracy calculation and performance results.
  - Noisy images used for testing.
- A compressed file containing all the required files for submission.
