//
// Created by Andrii Klykavka on 20.05.2025.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TextLine {
    char *text;
    size_t size;
    size_t capacity;

    void (*resize)(struct TextLine *self);

} TextLine;

void resizeLine(TextLine *line) {
    line->text = realloc(line->text, line->capacity * 2);
    line->capacity *= 2;
}

TextLine createTextLine(size_t capacity) {
    TextLine newLine;
    newLine.text = malloc(capacity * sizeof(char));
    newLine.capacity = capacity;
    newLine.size = 0;

    newLine.resize = resizeLine;
    return newLine;
}


typedef struct Buffer {
    TextLine *lines;
    size_t height;

    void (*free) (struct Buffer *self);
    void (*print) (struct Buffer *self);
    void (*append) (struct Buffer *self, char *text);
    void (*addLine) (struct Buffer *self);
    void (*insert) (struct Buffer *buffer, size_t line_idx, size_t char_idx, char *text);
    size_t (*search) (struct Buffer *buffer, char *text);
} Buffer;

void freeBuffer(Buffer *buffer) {
    free(buffer->lines);
    buffer->lines = NULL;
    buffer->height = 0;
}

void printBuffer(Buffer *buffer) {
    for(size_t i = 0; i < buffer->height; i++) {
        printf("%s\n", buffer->lines[i].text);
    }
}

void appendText(Buffer *buffer, char *text) {
    // Get pointer to last line -> Check if new test fits (if not - resize line) -> add text;
    size_t textLen = strlen(text);
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

void insert(Buffer *buffer, size_t line_idx, size_t char_idx, char *text) {
    if (line_idx >= buffer->height) {
        printf("Line index out of bounds.");
    }

    TextLine *line = buffer->lines + line_idx;

    if (char_idx > line->size) {
        printf("Char index out of bounds.");
    }

    size_t textLen = strlen(text);

    while (textLen > line->capacity - line->size) {
        line->resize(line);
    }

    memmove(line->text + char_idx + textLen, line->text + char_idx, textLen);
    line->size += textLen;
    memcpy(line->text + char_idx, text, textLen);

}

size_t search(Buffer *buffer, char *text) {
    size_t count = 0;
    for(size_t i = 0; i < buffer->height; i++) {
        TextLine *line = buffer->lines + i;
        char *pText = line->text;
        while((pText = strstr(pText, text)) != NULL) {
            // size_t index = pText - line->text;
            // results[count].lineIndex = i; // Collect all match indexes later
            // results[count].charIndex = index;
            count++;

            pText += strlen(text);
        }
    }

    return count;
}



Buffer createBuffer() {
    Buffer buffer;
    buffer.height = 0;
    buffer.lines = malloc(sizeof(TextLine) * 8);
    TextLine newLine = createTextLine(8);
    buffer.lines[buffer.height] = newLine;
    buffer.height++;

    buffer.free = freeBuffer;
    buffer.print = printBuffer;
    buffer.append = appendText;
    buffer.addLine = addLine;
    buffer.insert = insert;
    buffer.search = search;

    return buffer;
}