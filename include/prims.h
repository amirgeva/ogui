#ifndef H_CORE_PRIMS
#define H_CORE_PRIMS

// The following macro uses compiler trickery to check
// the size of a struct at compile time.
#define CHECK_STRUCT_SIZE(T,size)\
namespace { const char* stub_##T () { return (sizeof(T)!=size); } }

template<class T>
T Min(const T& a, const T& b)
{
  return (a<b?a:b);
}

template<class T>
T Max(const T& a, const T& b)
{
  return (a>b?a:b);
}

#endif // H_CORE_PRIMS

