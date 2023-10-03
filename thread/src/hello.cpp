#include <iostream>
#include <thread>

using namespace std;
void f() {
    cout << "Hello from thread " << this_thread::get_id() << endl;
    // this_thread::sleep_for(1);
}

int main(int argc, char **argv) {
    thread t(f);
    cout << "Main thread waiting..." << endl;
    t.join();
    return 0;
}