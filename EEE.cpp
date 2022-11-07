
#include "ecs36b_Common.h"

int
main(void)
{
  long MSize = 99999999; 
  try
    {
      std::cout << "MSize = " << MSize << std::endl;

      long int * m1 = (long int *) new long int[MSize * MSize];
      long int * m2 = (long int *) new long int[MSize * MSize];

      std::cout << "memory allocated\n";
      fflush(stdout);

    }
  catch (exception& e)
    {
      std::cout << "inside the exception\n";
      std::cout << "standard exception: " << e.what() << endl;
      std::cout << "typeid name = " << typeid(e).name() << std::endl;
    }
}
