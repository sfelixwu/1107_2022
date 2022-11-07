#include <iostream>

typedef bool (*Func_Ptr_t)(double); // typedef for pointers to function

template <typename T, int upper, int lower>
bool is_in_range (T arg_value)
{
  return ((arg_value <= upper) && (arg_value >= lower));
}

int
main(void)
{

#define _ECS36B_TYPEDEF_
#ifdef  _ECS36B_TYPEDEF_
  Func_Ptr_t func_ptr;                      // declare w/ typedef
#else   /* _ECS36B_TYPEDEF_ */
  bool (*func_ptr)(double);                 // declare
#endif  /* _ECS36B_TYPEDEF_ */
  
  func_ptr = is_in_range<double, 500, 0>;   // instantiate

  if ((*func_ptr)(35.0))
    std::cout << "it is true" << std::endl;

  fprintf(stdout, "%p\n", (void *) func_ptr); // 0x1078ce180

  return 0;
}
