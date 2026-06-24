#include <iostream>
#include <vector> // vector class-template definition
#include <algorithm> // copy algorithm
#include <iterator> // ostream_iterator iterator
#include <stdexcept> // out_of_range exception
using namespace std;

int main() {
   vector<int> values{1, 2, 3, 4, 5, 6};
   vector<int> integers{values.cbegin(), values.cend()};
   ostream_iterator<int> output{cout, " "};

   cout << "Vector integers contains: ";
   copy(integers.cbegin(), integers.cend(), output);

   cout << "\nFirst element of integers: " << integers.front()
      << "\nLast element of integers: " << integers.back();

   integers[0] = 7; // set first element to 7
   integers.at(2) = 10; // set element at position 2 to 10

   // insert 22 as 2nd element
   integers.insert(integers.cbegin() + 1, 22);

   cout << "\n\nContents of vector integers after changes: ";
   copy(integers.cbegin(), integers.cend(), output);

   // Access out-of-range element
   try {
      integers.at(100) = 777;
   }
   catch (out_of_range& outOfRange) {
      cout << "\n\nException: " << outOfRange.what();
   }

   integers.erase(integers.cbegin()); // erase first element
   cout << "\n\nVector integers after erasing first element: ";
   copy(integers.cbegin(), integers.cend(), output);

   // erase remaining elements
   integers.erase(integers.cbegin(), integers.cend());
   cout << "\nAfter erasing all elements, vector integers "
      << (integers.empty() ? "is" : "is not") << " empty";

   // insert elements from the vector values
   integers.insert(integers.cbegin(), values.cbegin(), values.cend());
   cout << "\n\nContents of vector integers before clear: ";
   copy(integers.cbegin(), integers.cend(), output);

   // empty integers; clear calls erase to empty a collection
   integers.clear();
   cout << "\nAfter clear, vector integers "
      << (integers.empty() ? "is" : "is not") << " empty" << endl;
}
