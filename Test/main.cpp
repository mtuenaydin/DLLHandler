/* 		Copyright (c) 2017 mtuenaydin
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:


THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.  */

#include <iostream>
#include "DLLHandler.h"



// import the SimpleLib into a class
IMPORT_LIB(SimpleLib, "Z:/Sandbox/VS_14.0/LibraryHandler/LibraryHandler/SimpleLib.dll",
	(
		DECLARE_LIB_CONST_FUNCTION_NO_PARAM (void, Function1);
		DECLARE_LIB_CONST_FUNCTION_ONE_PARAM (void, Function2, const int, a);
		DECLARE_LIB_CONST_FUNCTION_ONE_PARAM (void, Function3, const double, a);

		DECLARE_LIB_CLASS(SubLib,
			(
				void f() { std::cout << "sub lib\n"; }
			)
		);
	)
);



// import SimpleLib into the globale namespace
GIMPORT_LIB ( SimpleLib, "Z:/Sandbox/VS_14.0/LibraryHandler/LibraryHandler/SimpleLib.dll" )
DECLARE_GLOBLE_LIB_FUNCTION_NO_PARAM ( SimpleLib, void, Function1 );
DECLARE_GLOBLE_LIB_FUNCTION_ONE_PARAM ( SimpleLib, void, Function2, const int, a );
DECLARE_GLOBLE_LIB_FUNCTION_ONE_PARAM ( SimpleLib, void, Function3, const double, a );

int main()
{
	
	const SimpleLib lib;
	SimpleLib::SubLib sublib;

	if (gSimpleLib->IsLibraryValid())
	{
		Function1 ();
		Function2(2);
		Function3(2.4);
	}
	else
		std::cout << "couldn't load the DLL\n";

	std::cout << "\n\n";

	if ( lib.IsLibraryValid () )
	{
		lib.Function1 ();
		lib.Function2 ( 5 );
		lib.Function3 ( 3.1415 );
	}
	else
		std::cout << "couldn't load the DLL\n";
	

	return 0;
}

