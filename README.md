# DLLHandler
Simple Runtime DLL loading with full function signature in compile time.

# How to use
1. Include the .h and .cpp file to your project
2. use IMPORT_LIB to import a DLL file

IMPORT_LIB first Parameter need a class name, where all the (declared) functions will be stored. The second Parameter is the path to the dll file. The third Parameter need the declaration of the functions from the dll it is important that the function signature matches the signature from the imported dll, otherwise the result would be a nullptr which would be detected from an assert condition. To make the declaration easier the DLLHandler.h provide some macros to delcare functions in the IMPRT_LIB macro. For an example please look at the examples in the Test folder. 

# Support
Currently the DLLHandler supports only Windows, linux support will come soon.
