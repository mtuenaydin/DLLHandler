#include <iostream>

#ifdef MAKE_SIMPLE_API
#	define SIMPLE_API __declspec (dllexport)
#else
#	define SIMPLE_API __declspec (dllimport)
#endif

//#pragma comment(linker, "/export:Function1=?Function1@@YAXXZ")
void SIMPLE_API Function1()
{
	std::cout << "Function number one is successfully compiled and linked\n";
}

//#pragma comment(linker, "/export:Function2=?Function2@@YAXH@Z")
void SIMPLE_API Function2(int a)
{
	if (a < 0)
		a *= -1;
	std::cout << "Begin Loop:\n";
	for (int i = 0; i < a; i++)
		std::cout << i << ", ";
	std::cout << "End Loop.\n";
}

//#pragma comment(linker, "/export:Function3=?Function3@@YAXN@Z")
void SIMPLE_API Function3(double a)
{
	std::cout << "Imput value = " << a << std::endl;
}