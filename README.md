# OCR Digit Recognition using C and x86 Assembly

## Overview
This project implements a basic Optical Character Recognition (OCR) system for handwritten digits using a hybrid approach with C and x86 Assembly language. The system reads grayscale digit images, compares them against template images (0–9), and determines the closest match based on pixel differences.

The main objective of this project is to demonstrate low-level image processing and performance optimization using Assembly language integrated with C.

## Problem Statement

Digit recognition is an important task in many real-world applications such as:

- **Document digitization**
- **Form processing**
- **Postal code recognition**
- **Bank cheque processing**

Most modern OCR systems rely on complex machine learning models. This project instead demonstrates a simplified OCR approach using template matching and low-level programming techniques to recognize digits.

## Project Objectives

- **Implement a simple OCR system without external libraries.**

- **Demonstrate integration of C and Assembly language.**

- **Perform pixel-level image comparison.**

- **Use Makefile-based build automation.**

- **Show how Assembly can accelerate computational loops.**

## How It Works

The system follows these steps:

### 1. Image Input

A grayscale digit image (.pgm format) is given as input.

Example:
```
./ocr test_digit.pgm templates 784
```

### 2. Template Loading

The program loads template images for digits 0–9 from the templates/ directory.

Each template is a 28×28 grayscale image (784 pixels).

### 3. Pixel Comparison

The assembly function compares:
```
Input Image  vs  Template Image
```

For every pixel:
- **Convert to binary (threshold = 128)**
- **Compare pixel values**
- **Count mismatches**

### 4. Score Calculation

Each template receives a mismatch score.
```
lower score = better match
```

### 5. Digit Prediction

The template with the lowest mismatch score is selected as the recognized digit.

## Project Structure
```
ocr-asm/
│
├── main.c          # Main OCR program written in C
├── ocr.asm         # Assembly implementation of digit matching
├── Makefile        # Build automation script
│
├── templates/      # Template images for digits 0–9
│   ├── 0.pgm
│   ├── 1.pgm
│   ├── 2.pgm
│   └── ...
│
├── test_digit.pgm  # Example input digit image
│
└── README.md       # Project documentation
```

## File Description
### main.c

Responsible for:

- **Loading .pgm image files**

- **Reading input digit image**

- **Loading digit templates**

- **Calling the Assembly function**

- **Determining the best matching digit**

Key functions:
```
load_pgm()
```
Loads grayscale images into memory.
```
match_digit()
```
Calls the Assembly function to compare pixels.

### ocr.asm

Implements the core matching algorithm in Assembly.

Responsibilities:

- **Compare pixels of input and template images**

- **Apply thresholding (binary conversion)**

- **Count mismatched pixels**

- **Return mismatch score**

- **Using Assembly allows fast execution of repetitive pixel comparisons.**

### Makefile

Automates the build process.

Instead of manually compiling files, simply run:
```
make
```
The Makefile:

- **1. Compiles main.c**

- **2. Assembles ocr.asm**

- **3. Links both object files**

- **4. Produces executable ocr**

Commands used internally:
```
gcc -m32 -c main.c
nasm -f elf32 ocr.asm
gcc -m32 main.o ocr.o -o ocr
```

## Installation
### Requirements
Because the Makefile targets 32‑bit binaries, you need:

- **C compiler – gcc with 32‑bit support (-m32)**
- **NASM – Netwide Assembler, to assemble ocr.asm**
- **Make – to use the provided Makefile**

On Windows, you can build using e.g.:
- **MSYS2 / MinGW (with 32‑bit toolchain installed), or
WSL (Ubuntu, etc.) with gcc-multilib, nasm, and make.**

Install required tools:
```
sudo apt update
sudo apt install build-essential nasm gcc-multilib imagemagick
```

### Building the Project

Compile the program:
```
make
```

This will:
compile main.c → main.o (32‑bit)
assemble ocr.asm → ocr.o (ELF32)
link them into the ocr executable.

To clean build files:
```
make clean
```
### Running the Program
The program expects:
```
./ocr <test_digit.pgm> <templates_dir> <size>
```
Where:
- **<test_digit.pgm>: path to the input digit image (binary PGM, same dimensions as templates)**
- **<templates_dir>: directory containing 0.pgm … 9.pgm**
- **<size>: number of pixels in each image, i.e. width * height**

Example (from project root, assuming Unix‑like shell):
```
./ocr test_digit.pgm templates 784
```
for 28×28 images (e.g. MNIST‑style):

size = 28 * 28 = 784

Output example:
```
Digit 0 -> score 250
Digit 1 -> score 430
Digit 2 -> score 390
Digit 3 -> score 280
Digit 4 -> score 310
Digit 5 -> score 120
Digit 6 -> score 350
Digit 7 -> score 410
Digit 8 -> score 270
Digit 9 -> score 300

Recognized digit: 5
```

### Converting Images to PGM

The program requires 28×28 grayscale PGM images.

Convert PNG images using ImageMagick:
```
convert digit.png -resize 28x28 -colorspace Gray -depth 8 digit.pgm
```

Batch conversion:
```
for f in *.png; do convert "$f" -resize 28x28 -colorspace Gray -depth 8 "${f%.png}.pgm"; done
```

## Key Features

- **Hybrid C + Assembly implementation**

- **Template-based OCR**

- **Pixel-level image comparison**

- **Assembly optimized matching algorithm**

- **Works entirely offline**

- **Automated compilation using Makefile**

## Limitations

This project uses simple template matching, therefore:

- **Works best with aligned 28×28 images**

- **Sensitive to rotation or scaling**

- **Not suitable for complex handwriting**

Modern OCR systems use Machine Learning / Deep Learning models for better accuracy.

## Learning Outcomes

Through this project we learned:
- **Integration of C and x86 Assembly**
- **Low-level image processing**
- **File handling in C**
- **Memory management**
- **Build automation using Makefiles**
- **Optimization of loops using Assembly**

## Future Improvements

Possible improvements include:

- **Noise removal preprocessing**
- **Edge detection**
- **Feature extraction**
- **Machine learning based classification**
- **Support for full text recognition**