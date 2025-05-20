//
// Created by Andrii Klykavka on 20.05.2025.
//

#ifndef BUFFER_H
#define BUFFER_H


typedef struct TextLine {
    char *text;
    unsigned long size;
    unsigned long capacity;
} TextLine;

TextLine createTextLine(unsigned long capacity);
void resizeLine(TextLine *line);

typedef struct Buffer {
    TextLine *lines;
    unsigned long height;
} Buffer;

void initBuffer(Buffer *buffer);
void freeBuffer(Buffer *buffer);
void appendText(Buffer *buffer, char *text);
void addLine(Buffer *buffer);
void printBuffer(Buffer *buffer);




#endif //BUFFER_H
