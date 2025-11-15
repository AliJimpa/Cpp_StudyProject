#pragma once
#include <type_traits>

template <typename J, int N>
class JArray
{
private:
   static_assert(!std::is_function<J>::value, "J cannot be a function type");
   static_assert(!std::is_abstract<J>::value, "J cannot be an abstract class type");
   J m_Array[N];

public:
   int length() const
   {
      int al = sizeof(m_Array) / sizeof(m_Array[0]);
      return al;
   }

   J GetList()
   {
      return m_Array;
   }

   J &operator[](int index)
   {
      return m_Array[index];
   }

   const J &operator[](int index) const
   {
      return m_Array[index];
   }
};
