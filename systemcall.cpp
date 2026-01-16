#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid1, pid2, pid3, pid4;

    // Create first child process
    pid1 = fork();
    if (pid1 < 0) {
        cerr << "Fork failed for first child" << endl;
        return 1;
    } else if (pid1 == 0) {
        // First child process
        // Create second child process
        pid2 = fork();
        if (pid2 < 0) {
            cerr << "Fork failed for second child" << endl;
            return 1;
        } else if (pid2 == 0) {
            // Second child process
            // Create third child process
            pid3 = fork();
            if (pid3 < 0) {
                cerr << "Fork failed for third child" << endl;
                return 1;
            } else if (pid3 == 0) {
                // Third child process
                // Create fourth child process
                pid4 = fork();
                if (pid4 < 0) {
                    cerr << "Fork failed for fourth child" << endl;
                    return 1;
                } else if (pid4 == 0) {
                    // Fourth child process (deepest)
                    cout << "Fourth child PID: " << getpid() << endl;
                    return 0;
                } else {
                    // Third child waits for fourth child
                    wait(NULL);
                    cout << "Third child PID: " << getpid() << endl;
                }
            } else {
                // Second child waits for third child
                wait(NULL);
                cout << "Second child PID: " << getpid() << endl;
            }
        } else {
            // First child waits for second child
            wait(NULL);
            cout << "First child PID: " << getpid() << endl;
        }
        return 0;
    } else {
        // Parent waits for first child
        wait(NULL);
        cout << "Parent PID: " << getpid() << endl;
    }

    return 0;
}