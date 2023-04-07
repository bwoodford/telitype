#ifndef EDITOR_H
#define EDITOR_H

#include <termios.h>
#include <stdlib.h>
#include "GameLogic.h"

class Editor {
public:
  Editor();
  ~Editor();

  GameLogic::GameEvent currEvent;

  enum class Direction {
    FORWARD,
    BACKWARD
  };

  char getCurrentChar();
  void editorOpen(char *filename);
  void refreshScreen();
  void moveCursor(Direction d);

private:

  enum class Highlight: unsigned char {
    HL_NORMAL,
    HL_CORRECT,
    HL_INCORRECT,
  };

  typedef struct erow {
    int size;
    char* chars;
    unsigned char* hl;
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
  void abFree(struct abuf *ab);
  void abAppend(struct abuf *ab, const char *s, int len);
  void editorFreeRows(erow *row);
  int editorRowCxToRx(erow *row, int cx);
  int editorSyntaxToColor(Highlight hl);
  void editorHighlight();
  void editorUpdateSyntaxRow(erow *row);
  void colorCharacters(); 
};
#endif
