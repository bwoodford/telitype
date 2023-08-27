#ifndef TERMINAL_H
#define TERMINAL_H

#include <termios.h>
#include <stdlib.h>
#include "TextBuffer.h"

class Terminal {
public:
  Terminal();
  ~Terminal();

  void enableRawMode();
  void disableRawMode();
  void writeBuffer(TextBuffer *wb);

  // Getters - Setters
  int getWindowRows();
  int getWindowColumns();
  int getCursorRow();
  int getCursorColumn();
  void setCursorRow(int row);
  void setCursorColumn(int column);


private:
  struct termios orig_termios;

  int rawMode;

  int windowRows;
  int windowCols;

  int cursorRow;
  int cursorCol;

  int getCursorPosition(int *rows, int *cols);
  int setWindowSize(int *rows, int *cols);
};

#endif
