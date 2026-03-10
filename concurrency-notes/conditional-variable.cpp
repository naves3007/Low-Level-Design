#include<bits/stdc++.h>
using namespace std;

queue<int> q;
mutex m;
condition_variable cv;
bool done = false;

void producer(){
    for(int i = 1; i <= 5; i++){
        lock_guard<mutex> lock(m); // Lock_guard will automatically release the lock when it goes out of scope
        q.push(i);
        cout << "Produced: " << i << endl;
        cv.notify_one(); // Notify one waiting consumer
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate work
    }
    {
        lock_guard<mutex> lock(m);
        done = true; // Indicate that production is done
    }
    cv.notify_all(); // Notify all waiting consumers
}

void consumer(int id){
    while(true){
        unique_lock<mutex> lock(m); // Unique_lock allows us to manually control the locking and unlocking
        cv.wait(lock, []{ return !q.empty() || done; }); // Wait until there is something to consume or production is done
        if(!q.empty()){
            int item = q.front();
            q.pop();
            cout << "Consumer " << id << " consumed: " << item << endl;
        } else if(done){
            break; // Exit if production is done and queue is empty
        }
    }
}

int main(){
    thread p(producer);
    thread c(consumer,1);
    thread c2(consumer,2);

    p.join();
    c.join();
    c2.join();

    return 0;
}