#include <iostream>
#include <stdlib.h>
#include "Log.h"

using STRING = std::string;

extern int s_myvalue;

struct Vector2
{
    float X, Y;

    Vector2(float newX, float newY) : X(newX), Y(newY) {}

    Vector2 Add(const Vector2 &other) const
    {
        return Vector2(X + other.X, Y + other.Y);
    }

    Vector2 operator+(const Vector2 &other) const
    {
        return Add(other);
    }

    Vector2 Minus(const Vector2 &other) const
    {
        return Vector2(X - other.X, Y - other.Y);
    }

    Vector2 operator-(const Vector2 &other) const
    {
        return Minus(other);
    }

    Vector2 Multiply(const Vector2 &other) const
    {
        return Vector2(X * other.X, Y * other.Y);
    }

    Vector2 operator*(const Vector2 &other) const
    {
        return Multiply(other);
    }

    Vector2 Divide(const Vector2 &other) const
    {
        return Vector2(X / other.X, Y / other.Y);
    }

    Vector2 operator/(const Vector2 &other) const
    {
        return Divide(other);
    }

    bool Equal(const Vector2 &other) const
    {
        return (X == other.X && Y == other.Y);
    }

    bool operator==(const Vector2 &other) const
    {
        return Equal(other);
    }

    bool NotEqual(const Vector2 &other) const
    {
        return (X != other.X || Y != other.Y);
    }

    bool operator!=(const Vector2 &other) const
    {
        return NotEqual(other);
    }

    std::string ToString()
    {
        return "Comming Soon";
    }
};

std::ostream &operator<<(std::ostream &stream, const Vector2 &other)
{
    stream << other.X << "," << other.Y;
    return stream;
}

class Globalclass
{
public:
    Globalclass()
    {
        argoman = 900;
    }

    Globalclass(float target)
    {
        argoman = target;
    }

    ~Globalclass()
    {
        LOG("KKKOOOONII");
    }

    float argoman;

    void result()
    {
        LOG(argoman);
    }
};

struct entity
{
private:
    int score = -843;

public:
    // entity(){}
    entity() : score(100) {}
    entity(const int x) : score(x) {}

    bool changescore(int newscore)
    {
        if (newscore > 0)
        {
            score = newscore;
            return true;
        }
        else
        {
            return false;
        }
    }

    void printer()
    {
        LOG(score);
    }
};

void terst()
{
    Globalclass GC(400);
    GC.result();
}

class Player : public Globalclass
{
};

class Implicit
{
private:
    STRING m_Name;
    int m_Age;
    void interdius()
    {
        std::cout << m_Name << " = " << m_Age << std::endl;
    }

public:
    Implicit(const STRING &name) : m_Name(name), m_Age(-1) { interdius(); }
    Implicit(int age) : m_Name("Unkniwn"), m_Age(age) { interdius(); }
};

class ConstTest
{
private:
    int X = 900;

public:
    int GetX() const
    {
        // X = 50;
        return X;
    }

    ConstTest(int newx) : X(newx) {}
};

void printerg(const ConstTest &myclass)
{
    std::cout << myclass.GetX() << std::endl;
}

class ObjectLife
{
private:
public:
    ObjectLife()
    {
        LOG("Create");
    }
    ~ObjectLife()
    {
        LOG("Delet");
    }
};

class Scopeptr
{
private:
    ObjectLife *m_ptr;

public:
    Scopeptr(ObjectLife *ptr) : m_ptr(ptr)
    {
    }
    ~Scopeptr()
    {
        delete m_ptr;
    }
};
