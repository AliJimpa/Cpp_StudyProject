#include <iostream>
#include <queue>
#include <string>

struct Person {
    std::string name;
    int age;

    Person(std::string n, int a) : name(n), age(a) {}
};

int main() {
    // Create a queue of Person objects
    std::queue<Person> personQueue;

    // Enqueue some Person objects
    personQueue.push(Person("Alice", 30));
    personQueue.push(Person("Bob", 25));
    personQueue.push(Person("Charlie", 35));

    // Dequeue all elements and display their information
    while (!personQueue.empty()) {
        Person p = personQueue.front();
        std::cout << "Name: " << p.name << ", Age: " << p.age << std::endl;
        personQueue.pop();
    }

    return 0;
}

