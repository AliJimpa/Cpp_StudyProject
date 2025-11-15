#include <iostream>

#include <GLFW/glfw3.h>

#define PRINT(text) std::cout << text << std::endl

class singleton
{
private:
   int MyID = 0;
   /* data */
public:
   static singleton &get()
   {
      static singleton instance;
      return instance;
   }

   singleton()
   {
      PRINT("Create Singleton class");
   }

   void storeID(int newid)
   {
      PRINT("Store ID");
      MyID = newid;
   }

   int *GetIDptr()
   {
      PRINT("Get ID");
      return &MyID;
   }

   ~singleton()
   {
      PRINT("Destroy singleton Class");
   }
};

template <typename T, int N>
class TArray
{
private:
   T m_Array[N];

public:
   int length()
   {
      int al = sizeof(m_Array) / sizeof(m_Array[0]);
      return al;
   }

   T GetList()
   {
      return m_Array;
   }

   T &operator[](int index)
   {
      return m_Array[index];
   }
};

int Custommain()
{
   TArray<float, 2> ali;
   ali[0] = 5;
   ali[1] = 300;
   int arr[ali.length()] = ali.GetList();
   for (int item : arr)
   {
      PRINT(item);
   }
   PRINT("----");
   PRINT(ali.length());
}
