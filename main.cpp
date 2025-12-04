#include <cstddef>
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
    string s;
    getline(*file, s);

    if (s == prev) {
      break;
    }

    cout << s << endl;
  }
}

string promptUser() {
  cout << "Product name: ";

  string input;

  cin >> input;

  return input;
}

void addItem(fstream *file) {
  string val = promptUser();
  *file << val;
}

int main() {
  fstream file = openFile(PATH);

  file << "Banana\n";
  file << "Blueberries\n";
  file << "Apple\n";
  file << "Mango\n";
  file << "Kiwi\n";

  addItem(&file);

  // Reset file position pointer before switching from write to read
  file.seekg(0);
  printFileContents(&file);

  file.close();

  return 0;
}