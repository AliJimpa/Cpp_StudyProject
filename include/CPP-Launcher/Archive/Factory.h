#pragma once

class Factory
{
private:
    std::unordered_map<std::string, std::function<std::unique_ptr<Base>()>> registry;

public:
    template <typename T>
    void RegisterClass(const std::string &name)
    {
        registry[name] = []()
        { return std::make_unique<T>(); };
    }

    std::unique_ptr<Base> CreateInstance(const std::string &name)
    {
        if (registry.find(name) != registry.end())
        {
            return registry[name]();
        }
        return nullptr; // Return nullptr if class is not found
    }
};