#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

using namespace std;

class File {
public:
  File(char* path);
  ~File();

  typedef struct frow {
    string line;
    size_t length;
  } frow;

private:
  std::vector<frow> rows;
  int numrows;

  void load(char* path);
};
#endif
