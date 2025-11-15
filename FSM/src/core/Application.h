#pragma once
#include "Core.h"
#include <vector>
#include "Object.h"

std::vector<Object *> objects;

void Start()
{
    for (Object *obj : objects)
    {
        obj->OnBegin();
    }
}
void Update()
{
    for (Object *obj : objects)
    {
        if (obj->tick)
            obj->OnUpdate();
    }
}
void Finish()
{
    for (Object *obj : objects)
    {
        obj->OnEnd();
    }
}
template <typename T>
Object *SpawnObject()
{
    static_assert(std::is_base_of<Object, T>::value, "T must derive from Object");
    Object *obj = new T();
    obj->OnBegin();
    // Shoould Check Repetetily
    objects.push_back(obj);
    return obj;
}
bool DespawnObject(Object* target)
{
    for (Object *obj : objects)
    {
        if (obj == target)
        {
            PRINT("Hallo");
            return true;
        }
    }
    return false;
}
void Quit()
{
    bAppRuning = false;
}