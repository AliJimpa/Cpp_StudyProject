#include <iostream>
#include <vector>

#define PRINT(text) std::cout << text << std::endl

class Entity
{
private:
    int myID = -1;

public:
    Entity()
    {
        PRINT("Create");
    }
    ~Entity()
    {
        PRINT("Delete");
    }
    void Run()
    {
        PRINT("Execute");
    }
};

class String
{
private:
    char *m_Buffer;
    unsigned int m_size;

public:
    String(const char *string)
    {
        m_size = strlen(string);
        m_Buffer = new char[m_size + 1];
        // for (size_t i = 0; i < m_size; i++)
        // {
        //    m_Buffer[i] = String[i];
        // }
        memcpy(m_Buffer, string, m_size);
        m_Buffer[m_size] = 0;
    }

    String(const String &other) : m_size(other.m_size)
    {
        std::cout << "CopyString" << std::endl;
        m_Buffer = new char[m_size + 1];
        memcpy(m_Buffer, other.m_Buffer, m_size + 1);
    }

    ~String()
    {
        delete[] m_Buffer;
    }

    char &operator[](unsigned int index)
    {
        return m_Buffer[index];
    }

    friend std::ostream &operator<<(std::ostream &stream, const String &other);
};

std::ostream &operator<<(std::ostream &stream, const String &other)
{
    stream << other.m_Buffer;
    return stream;
}

void PrintString(const String &string)
{
    std::cout << string << std::endl;
}

class Scopedptr
{
private:
    Entity *m_Object;

public:
    Scopedptr(Entity *Object) : m_Object(Object)
    {
    }
    ~Scopedptr()
    {
        delete m_Object;
    }

    Entity *GetObject() const
    {
        return m_Object;
    }

    Entity *operator->()
    {
        return m_Object;
    }
};

struct Segment
{
    float x1, y1, z1;

    Segment()
    {
        PRINT("Create - Empty");
    }

    Segment(float nx, float ny, float nz) : x1(nx), y1(ny), z1(nz)
    {
        PRINT("Create by detatil - " << nx);
    }

    Segment(const Segment &ns) : x1(ns.x1), y1(ns.y1), z1(ns.z1)
    {
        PRINT("Create by refrence - " << ns.x1);
    }
};

std::ostream &operator<<(std::ostream &stream, const Segment &other)
{
    stream << "{" << other.x1 << "," << other.y1 << "," << other.z1 << "}";
    return stream;
}

std::vector<Segment> Cratedynamicarray()
{
    std::vector<Segment> vertexs;
    vertexs.reserve(3);
    vertexs.emplace_back(1111, 200, 100);
    vertexs.emplace_back(3, 2, 7);
    vertexs.emplace_back(0, 0, 0);
    return vertexs;
}
