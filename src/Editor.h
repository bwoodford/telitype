#ifndef EDITOR_H
#define EDITOR_H

#include <termios.h>

class Editor {
public:
  Editor();
  ~Editor();

private:
  typedef struct erow {
    int size;
    char* chars;
    // size of render
    int rsize;
    char* render;
  } erow;

  struct Config {
    // index for chars field in erow
    int cx, cy;
    // index for render field in erow
    int rx;
    int screenrows;
    int screencols;
    int coloff;
    int rowoff;
    int numrows;
    erow* row;
    struct termios orig_termios;
  };

  Config E;
  int getWindowSize(int *rows, int *cols);
  int getCursorPosition(int *rows, int *cols);
  void editorRefreshScreen();
  void enableRawMode();
  void disableRawMode();
};
#endif
