#include <bits/stdc++.h>
using namespace std;
int globalCounter = 0;

void print(int counter, const char *c) {
  for (int i = 0; i < 100000; i++) {
    int local = 0;
    local += 1;
    globalCounter += local;
  }
}

int main() {
  int counter = 100000;
  thread t1(print, counter, "Thread 1");
  thread t2(print, counter, "Thread 2");
  t1.join();
  t2.join();

  cout << "Global Counter: " << globalCounter << endl;
  cout << "Counter: " << 2 * counter << endl;

  return 0;
}