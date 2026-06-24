#include <vector>
#include <iostream>
#include <set> // multiset class-template definition
#include <algorithm> // copy algorithm
#include <iterator> // ostream_iterator
using namespace std;

int main() {
   multiset<int, less<int>> intMultiset; // multiset of ints

   cout << "There are currently " << intMultiset.count(15)
      << " values of 15 in the multiset\n";

   intMultiset.insert(15); // insert 15 in intMultiset
   intMultiset.insert(15); // insert 15 in intMultiset
   cout << "After inserts, there are " << intMultiset.count(15)
      << " values of 15 in the multiset\n\n";

   // find 15 in intMultiset; find returns iterator
   auto result = intMultiset.find(15);

   if (result != intMultiset.end()) { // if iterator not at end
      cout << "Found value 15\n"; // found search value 15
   }

   // find 20 in intMultiset; find returns iterator
   result = intMultiset.find(20);
   if (result == intMultiset.end()) { // will be true hence
      cout << "Did not find value 20\n"; // did not find 20
   }

   // insert elements of array a into intMultiset
   vector<int> a{7, 22, 9, 1, 18, 30, 100, 21, 85, 13};
   intMultiset.insert(a.cbegin(), a.cend());
   cout << "\nAfter insert, intMultiset contains:\n";
   ostream_iterator<int> output{cout, " "};
   copy(intMultiset.begin(), intMultiset.end(), output);
   cout << "\n\nLower bound of 22: "
      << *(intMultiset.lower_bound(22)); //>=22
   cout << "\nUpper bound of 22: " << *(intMultiset.upper_bound(22)); // >22

   // use equal_range to determine lower and upper bound
   // of 22 in intMultiset
   auto p = intMultiset.equal_range(22);

   cout << "\n\nequal_range of 22:\n Lower bound: "
      << *(p.first) << "\n Upper bound: " << *(p.second);
   cout << endl;
}