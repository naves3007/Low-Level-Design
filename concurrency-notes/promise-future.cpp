#include<bits/stdc++.h>
using namespace std;

void compute(promise<int> p){
    this_thread::sleep_for(chrono::seconds(2)); // Simulate some work
    p.set_value(42); // Set the value in the promise
}

int main(){
    promise<int>p;
    future<int>f = p.get_future(); // Get the future associated with the promise

    thread t(compute, move(p));
    int result = f.get(); // Wait for the result from the promise
    cout << "Result: " << result << endl;
    t.join(); // Wait for the thread to finish
}