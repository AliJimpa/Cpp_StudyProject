#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class ControlledThread {
private:
    std::thread workerThread;
    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;
    bool stop = false;
    bool running = false;  // New flag to indicate if the thread is running a task
    std::function<void()> task;

    // Function executed by the thread
    void threadFunction() {
        std::unique_lock<std::mutex> lock(mtx);
        while (!stop) {
            cv.wait(lock, [this]() { return ready || stop; });
            if (ready && task) {
                running = true;  // Set running to true when task starts
                // Perform the thread's task
                task();
                running = false;  // Set running to false when task is done
                ready = false;  // Reset the flag
            }
        }
    }

public:
    // Constructor: creates the thread but it waits for the signal
    ControlledThread() {
        workerThread = std::thread(&ControlledThread::threadFunction, this);
    }

    // Destructor: stops the thread and joins it
    ~ControlledThread() {
        {
            std::lock_guard<std::mutex> lock(mtx);
            stop = true;
            cv.notify_all();
        }
        workerThread.join();
    }

    // Function to notify the thread to start its task
    void run(const std::function<void()> &newTask) {
        {
            std::lock_guard<std::mutex> lock(mtx);
            task = newTask;
            ready = true;
        }
        cv.notify_all();
    }

    // Method to check if the thread is running a task
    bool isRunning() {
        std::lock_guard<std::mutex> lock(mtx);
        return running;
    }
};