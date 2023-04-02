#ifndef EDITOR_H
#define EDITOR_H

#include <termios.h>
#include <stdlib.h>

class Editor {
public:
  Editor();
  ~Editor();

  enum direction {
    FORWARD,
    BACKWARD
  };

  char getCurrentChar();
  void editorOpen(char *filename);
  void refreshScreen();
  void moveCursor(direction d);

private:
  typedef struct erow {
    int size;
    char* chars;
    // size of render
    int rsize;
    char* render;
  } erow;

  struct abuf {
    char *b;
    int len;
  };

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
  void enableRawMode();
  void disableRawMode();
  void editorAppendRow(char *s, size_t len);
  void editorUpdateRow(erow *row);
  void editorScroll();
  void editorDrawRows(struct abuf *ab);
  // MOVE AB TO DIFFERENT FILE
  void abFree(struct abuf *ab);
  void abAppend(struct abuf *ab, const char *s, int len);
  int editorRowCxToRx(erow *row, int cx);
};
#endif
