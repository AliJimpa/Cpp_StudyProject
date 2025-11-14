#include <iostream>

#define LOG(x) std::cout << x << std::endl

static void print_bytes(const void *object, size_t size)
{
#ifdef __cplusplus
    const unsigned char *const bytes = static_cast<const unsigned char *>(object);
#else  // __cplusplus
    const unsigned char *const bytes = object;
#endif // __cplusplus

    size_t i;

    printf("[ ");
    for (i = 0; i < size; i++)
    {
        printf("%02x ", bytes[i]);
    }
    printf("]\n");
}

struct Entity
{
    int x, y;

    int *GetPosition()
    {
        return &x;
    }
};

int main()
{
    Entity e = {5, 8};

    print_bytes(&e,sizeof e);

    char *r = (char *)e.GetPosition();

    print_bytes(r,sizeof r);
    LOG((int)r[0]);
    
}