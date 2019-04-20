#if defined(__GNUC__) &&  (__GNUC__ * 100 + __GNUC_MINOR__) >= 303
#define _X_NONNULL(args...)  __attribute__((nonnull(args)))
#else
#define _X_NONNULL(...)  /* */
#endif

#include <cstdio>
#include <vector>
#include <string>
#include <math.h>
#include <map>
#include <cassert>
#include <limits.h>

#define kk() 1

int main(int argc, char* argv[])
{
  int b = kk( );

  std::vector<float> resArr;
  float res = cos(3.14f);
  
  int a = UINT_MAX;

  assert(res!=0.f && "bad result!");

  resArr.push_back(res);

  const char* hola = "hola, que tal,com estas?";

  printf("el resultat es : %f\n",resArr[0]);

  return 0;
}
