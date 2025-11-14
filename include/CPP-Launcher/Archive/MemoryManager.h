class MemoryManager
{
private:
    size_t totalSize;  // Total RAM block size
    size_t usedSize;   // How much memory is used
    void *memoryBlock; // Pointer to the allocated memory

public:
    MemoryManager(size_t size) : totalSize(size), usedSize(0)
    {
        memoryBlock = std::malloc(size); // Allocate block
        if (!memoryBlock)
        {
            throw std::bad_alloc(); // If allocation fails
        }
    }

    void *Allocate(size_t size)
    {
        if (usedSize + size > totalSize)
        {
            throw std::bad_alloc(); // Prevent overflow
        }
        void *ptr = static_cast<char *>(memoryBlock) + usedSize;
        usedSize += size;
        return ptr;
    }

    void FreeAll()
    {
        usedSize = 0; // Reset memory usage
    }

    ~MemoryManager()
    {
        std::free(memoryBlock); // Free allocated block
    }
};