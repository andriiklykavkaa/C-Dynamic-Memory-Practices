//
// Created by Andrii Klykavka on 20.05.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TextLine {
    char *text;
    unsigned long size;
    unsigned long capacity;
} TextLine;

TextLine createTextLine(unsigned long capacity) {
    TextLine newLine;
    newLine.text = malloc(capacity * sizeof(char));
    newLine.capacity = capacity;
    newLine.size = 0;
    return newLine;
}

void resizeLine(TextLine *line) {
    line->text = realloc(line->text, line->capacity * 2);
    line->capacity *= 2;
}

typedef struct Buffer {
    TextLine *lines;
    unsigned long height;
} Buffer;


void initBuffer(Buffer *buffer) {
    buffer->height = 0;
    buffer->lines = malloc(sizeof(TextLine) * 8);
    TextLine newLine = createTextLine(8);
    buffer->lines[buffer->height] = newLine;
    buffer->height++;
}

void freeBuffer(Buffer *buffer) {
    free(buffer->lines);
    buffer->lines = NULL;
    buffer->height = 0;
}

void appendText(Buffer *buffer, char *text) {
    // Get pointer to last line -> Check if new test fits (if not - resize line) -> add text;
    unsigned long textLen = strlen(text);
    TextLine *pLastLine = &buffer->lines[buffer->height-1];
    while (textLen + pLastLine->size > pLastLine->capacity) {
        resizeLine(pLastLine);
    }

    memcpy(pLastLine->text + pLastLine->size, text, textLen);
    pLastLine->size += textLen;
}

void addLine(Buffer *buffer) {
    TextLine newLine = createTextLine(8);
    buffer->lines[buffer->height] = newLine;
    buffer->height++;
}

void printBuffer(Buffer *buffer) {
    for(int i = 0; i < buffer->height; i++) {
        printf("%s\n", buffer->lines[i].text);
    }
}