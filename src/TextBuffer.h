#ifndef TEXTBUFFER_H 
#define TEXTBUFFER_H

class TextBuffer {
public:
  TextBuffer();
  ~TextBuffer();

  void append(const char *s, int len);
  char* getBuffer();
  int getLength();
  void print();

private: 
  int length; 
  char *buffer;

};
#endif
