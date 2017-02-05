/* 		Copyright (c) 2017 mtuenaydin
	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.  */

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
