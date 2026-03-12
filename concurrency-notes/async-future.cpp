#include <bits/stdc++.h>
using namespace std;

int compute() {
  return 42; // Simulate some work and return a value
}

int main() {
  future<int> f = async(launch::async,
                        compute); // Run compute asynchronously and get a future
  int result = f.get();           // Wait for the result from the async function
  cout << "Result: " << result << endl;
}

// Run: g++ -std=c++14 async-future.cpp -o async-future && ./async-future