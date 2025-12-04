#include <fstream>
#include <iostream>

using namespace std;

const string PATH = "inventory.txt";

fstream openFile(string path) {
  // Open file for reading and writing
  fstream stream(path, ios::in | ios::out);
  // TODO: what if file does not exist?
  // I know that if opened in write mode and the file does not exist, it will be
  // created. However, read mode will throw an exception.

  return stream;
}

void printFileContents(fstream *file) {
  string s;
  string prev;
  while (true) {
    prev = s;
    getline(*file, s);

    if (s == prev) {
      break;
    }

    cout << s << endl;
  }
}

int main() {
  fstream file = openFile(PATH);

  printFileContents(&file);
  return 0;
}