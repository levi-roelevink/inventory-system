#include <cstddef>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iostream>

using namespace std;

const string PATH = "inventory.txt";

const int LIST_INVENTORY = 1;
const int ADD_PRODUCT = 2;
const int REMOVE_PRODUCT = 3;
const int EXIT = 4;
const string PRINT_MENU = "**********\n(1) List inventory\n(2) Add "
                          "product\n(3) Remove product\n(4) Exit "
                          "program\n**********\nSelect an option: ";

int selectIntBetweenBounds(int lowerBound, int upperBound) {
  int result;

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

string promptUserForProduct() {
  cout << "Product name: ";

  string input;
  cin >> input;
  // TODO: What if there's a whitespace character?
  // Also try adding multiple items to see if they're formatted correctly in the
  // txt file

  return input;
}

void addProduct(string path) {
  ofstream of;

  // Opening file using ofstream
  of.open(path, ios::app);
  if (!of) {
    cout << "Unable to find inventory." << endl;
  } else {
    string val = promptUserForProduct();

    of << "\n" << val;
    of.close();
  }
}

int listInventory(string path, bool numbered) {
  // Open file in read mode
  ifstream file(path);
  cout << "Current inventory:\n**********\n";

  string s, prev;
  int count = 0;

  while (true) {
    prev = s;
    getline(file, s);

    if (s == prev || s == "") {
      break;
    }

    count++;
    if (numbered) {
      cout << "(" << count << ") " << s << endl;
    } else {
      cout << s << endl;
    }
  }

  file.close();

  if (count == 0) {
    cout << "There are currently no items in inventory." << endl;
  }
  cout << "*********";

  return count;
}

void removeProduct(string path) {
  int products = listInventory(path, true);

  cout << "\nSelect a product to remove (0 to cancel): ";
  int input = selectIntBetweenBounds(0, products);

  if (input == 0) {
    return;
  }

  cout << "Selected: " << input << endl;
  // TODO: How to remove this product from the inventory?
}

// 1. Print menu options
// 2. Prompt user for menu selection
// 3. Call selected functionality
int menuSelection() {
  while (true) {
    cout << PRINT_MENU;
    int input = selectIntBetweenBounds(1, 4);

    switch (input) {
    case LIST_INVENTORY:
      listInventory(PATH, false);
      break;
    case ADD_PRODUCT:
      addProduct(PATH);
      break;
    case REMOVE_PRODUCT:
      removeProduct(PATH);
      break;
    case EXIT:
      return 0;
    }

    cout << "\n";
  }
}

void loadMockData(string path) {
  // Open file for reading and writing
  ofstream of;
  of.open(path);
  if (!of) {
    cout << "Unable to find inventory. Please try again." << endl;
    return;
  }

  of << "Banana\n";
  of << "Blueberries\n";
  of << "Apple\n";
  of << "Mango\n";
  of << "Kiwi\n";

  of.close();
  cout << "Loaded mock data.\n" << endl;
}

int main() {
  loadMockData(PATH);

  int menuSelector = menuSelection();

  cout << "Goodbye!" << endl;
  return 0;
}

// addItem(&file);

// Reset file position pointer before switching from write to read
// file.seekg(0);
// printFileContents(&file)