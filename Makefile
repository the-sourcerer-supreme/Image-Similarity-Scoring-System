# Makefile for OCR (C + Assembly)

CC = gcc
ASM = nasm
CFLAGS = -m32 -Wall -O2
LDFLAGS = -m32 -no-pie
TARGET = ocr

OBJS = main.o ocr.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

ocr.o: ocr.asm
	$(ASM) -f elf32 $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
