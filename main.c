#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1024

// declare assembly function
extern int match_digit(const unsigned char *img, const unsigned char *tmpl, int size);

// function to load pgm file into array
unsigned char* load_pgm(const char *filename, int *size) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("open");
        return NULL;
    }

    char magic[3];
    if (!fgets(magic, sizeof(magic), f)) {
        fclose(f);
        return NULL;
    }

    if (strncmp(magic, "P5", 2) != 0) {
        printf("Not a valid PGM (must be binary P5)\n");
        fclose(f);
        return NULL;
    }

    int w, h, maxval;
    // skip comments
    int c;
    while ((c = fgetc(f)) == '#') {
        while (fgetc(f) != '\n');
    }
    ungetc(c, f);

    if (fscanf(f, "%d %d", &w, &h) != 2) {
        fclose(f);
        return NULL;
    }
    if (fscanf(f, "%d", &maxval) != 1) {
        fclose(f);
        return NULL;
    }

    fgetc(f); // consume single whitespace after header

    int img_size = w * h;
    unsigned char *data = malloc(img_size);
    if (!data) {
        fclose(f);
        return NULL;
    }

    if (fread(data, 1, img_size, f) != img_size) {
        printf("Error reading pixel data\n");
        free(data);
        fclose(f);
        return NULL;
    }

    fclose(f);
    *size = img_size;
    return data;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Usage: %s test_digit.pgm templates_dir size\n", argv[0]);
        return 1;
    }

    int input_size;
    unsigned char *input = load_pgm(argv[1], &input_size);
    if (!input) return 1;

    int tmpl_size = atoi(argv[3]);

    int best_digit = -1;
    int best_score = 1e9;

    char path[256];
    for (int d = 0; d <= 9; d++) {
        snprintf(path, sizeof(path), "%s/%d.pgm", argv[2], d);

        int tsz;
        unsigned char *tmpl = load_pgm(path, &tsz);
        if (!tmpl) continue;

        if (tsz != tmpl_size) {
            printf("Template %d size mismatch: got %d, expected %d\n", d, tsz, tmpl_size);
            free(tmpl);
            continue;
        }

        int score = match_digit(input, tmpl, tmpl_size);
        printf("Digit %d -> score %d\n", d, score);

        if (score < best_score) {
            best_score = score;
            best_digit = d;
        }

        free(tmpl);
    }

    printf("Recognized digit: %d\n", best_digit);
    free(input);
    return 0;
}
