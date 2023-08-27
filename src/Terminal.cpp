#include "Terminal.h"
#include "TextBuffer.h"
#include <stdexcept>
#include <cstring>
#include <sys/ioctl.h>
#include <unistd.h>
#include "iostream"

using namespace std;

Terminal::Terminal() {
  rawMode = 0;
  setWindowSize(&windowRows, &windowCols);
}

Terminal::~Terminal() { 
  disableRawMode(); 
}

int Terminal::setWindowSize(int *rows, int *cols) {
  struct winsize ws;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
    if (write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
      return -1;
  } else {
    *cols = ws.ws_col;
    *rows = ws.ws_row;
  }
  return 0;
}

int Terminal::getCursorPosition(int *rows, int *cols) {
  if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
    return -1;

  char buf[32];
  unsigned int i = 0;
  while (i < sizeof(buf) - 1) {
    if (read(STDIN_FILENO, &buf[i], 1) != 1)
      break;
    if (buf[i] == 'R')
      break;
    i++;
  }
  buf[i] = '\0';

  if (buf[0] != '\x1b' || buf[1] != '[')
    return -1;
  if (sscanf(&buf[2], "%d;%d", rows, cols) != 2)
    return -1;

  return -1;
}

void Terminal::setCursorColumn(int x) {
  if (x < 0) this->cursorCol = 0;
  this->cursorCol = x;
}

void Terminal::setCursorRow(int y) {
  if (y < 0) this->cursorRow = 0;
  this->cursorRow = y;
}

void Terminal::writeBuffer(TextBuffer *wb) {
  TextBuffer tb;
  // turn on cursor hiding
  tb.append("\x1b[?25l", 6);
  // set cursor to first row, first column 
  tb.append("\x1b[H", 3);

  tb.append(wb->getBuffer(), wb->getLength());

  char buf[32];
  // cursor move
  //snprintf(buf, sizeof(buf), "\x1b[%d;%dH", (cursorRow - E.rowoff) + 1, (cursorCol - E.coloff) + 1);
  snprintf(buf, sizeof(buf), "\x1b[%d;%dH", cursorRow, cursorCol);

  tb.append(buf, strlen(buf));
  // turn off cursor hiding
  tb.append("\x1b[?25h", 6);

  write(STDOUT_FILENO, tb.getBuffer(), tb.getLength());
}

void Terminal::disableRawMode() {
  if (!rawMode) return;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1) {
    throw std::runtime_error("disableRawMode");
  }
  write(STDOUT_FILENO, "\n", 2);
}

void Terminal::enableRawMode() {
  if (rawMode) return;

  if (tcgetattr(STDIN_FILENO, &orig_termios) == -1) {
    throw std::runtime_error("enableRawMode");
  }

  struct termios raw = orig_termios;
  raw.c_iflag &= ~(BRKINT | INPCK | ISTRIP | ICRNL | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;

  if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1) {
    throw std::runtime_error("enableRawMode");
  }

  rawMode = 1;
}

int Terminal::getCursorRow() {
  return cursorRow;
}

int Terminal::getCursorColumn() {
  return cursorCol;
}

int Terminal::getWindowRows() {
  return windowRows;
}

int Terminal::getWindowColumns() {
  return windowCols;
}
