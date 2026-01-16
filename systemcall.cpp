#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main() {
    pid_t pid1, pid2, pid3, pid4, pid5;

    // Main parent process
    cout << "Parent PID: " << getpid() << endl;

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
                    // Fourth child process
                    // Create fifth child process
                    pid5 = fork();
                    if (pid5 < 0) {
                        cerr << "Fork failed for fifth child" << endl;
                        return 1;
                    } else if (pid5 == 0) {
                        // Fifth child process (deepest) - prints first
                        cout << "Fifth child PID: " << getpid() << endl;
                        return 0;
                    } else {
                        // Fourth child waits for fifth child
                        wait(NULL);
                        sleep(1);
                        cout << "Fourth child PID: " << getpid() << endl;
                    }
                } else {
                    // Third child waits for fourth child
                    wait(NULL);
                    sleep(2);
                    cout << "Third child PID: " << getpid() << endl;
                }
            } else {
                // Second child waits for third child
                wait(NULL);
                sleep(3);
                cout << "Second child PID: " << getpid() << endl;
            }
        } else {
            // First child waits for second child
            wait(NULL);
            sleep(4);
            cout << "First child PID: " << getpid() << endl;
        }
        return 0;
    } else {
        // Parent waits for first child
        wait(NULL);
    }

    return 0;
}