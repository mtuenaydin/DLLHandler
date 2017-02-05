#include <iostream>
#include "DLLHandler.h"

// This is the way how DLLHandler works
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


int main()
{
	SimpleLib lib;
	SimpleLib::SubLib sublib;
	const SimpleLib lib2;

	lib2.Function1 ();

	if (lib.IsLibraryValid())
	{
		lib.Function1 ();
		lib.Function2(2);
		lib.Function3(2.4);
	}
	else
		std::cout << "couldn't load the DLL\n";

	return 0;
}

