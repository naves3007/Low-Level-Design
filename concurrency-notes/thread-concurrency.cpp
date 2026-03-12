#include <bits/stdc++.h>
using namespace std;

void print(const char *c) {
  for (int i = 1; i <= 3; i++) {
    cout << c << " " << i << endl;
    this_thread::sleep_for(chrono::milliseconds(10));
  }
}
int main() {
  thread t1(print, "Thread 1");
  thread t2(print, "Thread 2");
  t1.join();
  t2.join();

  cout << "Main thread finished" << endl;

  return 0;
}