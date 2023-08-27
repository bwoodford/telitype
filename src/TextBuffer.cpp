#include "TextBuffer.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

TextBuffer::TextBuffer() {
  buffer = NULL;
  length = 0;
}

TextBuffer::~TextBuffer() {
  free(buffer);
}

void TextBuffer::append(const char *s, int sLength) {
  char *newBuffer = (char*)realloc(buffer, length + sLength);
  if (newBuffer == NULL) return;
  memcpy(&newBuffer[length], s, sLength);
  buffer = newBuffer;
  length += sLength;
}

char* TextBuffer::getBuffer() {
  return buffer;
}

int TextBuffer::getLength() {
  return length;
}

void TextBuffer::print() {
  cout << buffer << endl;
}
