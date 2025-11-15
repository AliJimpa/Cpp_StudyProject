#ifndef SIMPLEMAP_H
#define SIMPLEMAP_H

#include <vector>
#include <utility>
#include <algorithm>

namespace AJimpa
{
    template <typename Key, typename Value>
class SimpleMap {
private:
    std::vector<std::pair<Key, Value>> data;

public:
    // Insert a key-value pair
    void insert(const Key& key, const Value& value) {
        // Find if the key already exists
        auto it = std::find_if(data.begin(), data.end(), [&key](const std::pair<Key, Value>& element) {
            return element.first == key;
        });

        if (it != data.end()) {
            // Update existing key
            it->second = value;
        } else {
            // Insert new key-value pair
            data.push_back(std::make_pair(key, value));
        }
    }

    // Find a value by key
    Value* find(const Key& key) {
        auto it = std::find_if(data.begin(), data.end(), [&key](const std::pair<Key, Value>& element) {
            return element.first == key;
        });

        if (it != data.end()) {
            return &it->second;
        }

        return nullptr;
    }

    // Remove a key-value pair
    void remove(const Key& key) {
        data.erase(std::remove_if(data.begin(), data.end(), [&key](const std::pair<Key, Value>& element) {
            return element.first == key;
        }), data.end());
    }

    // Print all key-value pairs
    void print() const {
        for (const auto& pair : data) {
            std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
        }
    }
};

} // namespace AJimpa

#endif // SIMPLEMAP_H
