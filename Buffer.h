//
// Created by Andrii Klykavka on 20.05.2025.
//

#ifndef BUFFER_H
#define BUFFER_H


typedef struct TextLine {
    char *text;
    size_t size;
    size_t capacity;
    void (*resize)(struct TextLine *self);
} TextLine;

typedef struct Buffer {
    TextLine *lines;
    size_t height;
    void (*free)(struct Buffer *self);
    void (*print)(struct Buffer *self);
    void (*append)(struct Buffer *self, char *text);
    void (*addLine)(struct Buffer *self);
    void (*insert) (struct Buffer *buffer, size_t line_idx, size_t char_idx, char *text);
    size_t (*search) (struct Buffer *buffer, char *text);
} Buffer;

TextLine createTextLine(size_t capacity);
Buffer createBuffer(void);
#endif //BUFFER_H
