#ifndef FILEROW_H
#define FILEROW_H

#include <string>

using namespace std;

class FileRow {
public:
  FileRow(string chars, int length) : chars(chars), length(length){};

  int length;
  string chars;
};
#endif
