#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

const string PATH = "inventory.txt";

const int LIST_INVENTORY = 1;
const int ADD_PRODUCT = 2;
const int REMOVE_PRODUCT = 3;
const int EXIT = 4;
const string PRINT_MENU =
    "**********\n(1) List inventory\n(2) Add "
    "product\n(3) Remove product\n(4) Exit program\n**********\n";

int selectBetweenBounds(int lowerBound, int upperBound) {
  int result;

  cout << "Select an option: ";
  cin >> result;
  // TODO: What if input is not an integer
  while (result < lowerBound || result > upperBound) {
    cout << "\nOption must be between " << lowerBound << " and " << upperBound
         << ".\nSelect an option: ";
    cin >> result;
  }

  cout << "\n";
  return result;
}

void addProduct() { cout << "Add product" << endl; }

void removeProduct() { cout << "Remove product" << endl; }

void listInventory(fstream *file) {
  // Reset file position pointer before switching from write to read
  file->seekp(0);

  cout << "Current inventory:\n**********\n";

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

  cout << "*********\n";
}

// 1. Print menu options
// 2. Prompt user for menu selection
// 3. Call selected functionality
int menuSelection(fstream *file) {
  while (true) {
    cout << PRINT_MENU;
    int input = selectBetweenBounds(1, 4);

    switch (input) {
    case LIST_INVENTORY:
      listInventory(file);
      break;
    case ADD_PRODUCT:
      addProduct();
      break;
    case REMOVE_PRODUCT:
      removeProduct();
      break;
    case EXIT:
      return 0;
    }

    cout << "\n";
  }
}

fstream openFile(string path) {
  // Open file for reading and writing
  fstream stream(path, ios::in | ios::out);
  if (!stream) {
    // File did not exist yet, so a file is created with an output file stream
    ofstream oStr(path);
    oStr.close();

    return fstream(path, ios::in | ios::out);
  }

  return stream;
}

string promptUser() {
  cout << "Product name: ";

  string input;
  cin >> input;
  // TODO: What if there's a whitespace character?
  // Also try adding multiple items to see if they're formatted correctly in the
  // txt file

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

  int menuSelector = menuSelection(&file);

  file.close();
  cout << "Goodbye!" << endl;
  return 0;
}

// addItem(&file);

// Reset file position pointer before switching from write to read
// file.seekg(0);
// printFileContents(&file);