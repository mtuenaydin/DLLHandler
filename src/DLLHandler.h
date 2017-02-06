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

#ifndef DLLHANDLER_H
#define DLLHANDLER_H
#pragma once
#include <assert.h>
#include <memory>

#ifndef SDH_NAMESPACE
#	define SDH_NAMESPACE
#	define SDH_BEGIN	namespace SDH {  /*SDH = Simple DLL Handler*/
#	define SDH_END		}
#endif

#define DECLARE(...) __VA_ARGS__ 
#define DECLARE_LIB_FUNCTION_NO_PARAM(ReturnType, FunctionName) ReturnType FunctionName () { return m_handler->GetFunction<ReturnType>(#FunctionName) ();}
#define DECLARE_LIB_FUNCTION_ONE_PARAM(ReturnType, FunctionName, ParamType1, ParamName1) ReturnType FunctionName (ParamType1 ParamName1) { return m_handler->GetFunction<ReturnType>(#FunctionName, ParamName1) (ParamName1);}
#define DECLARE_LIB_FUNCTION_TWO_PARAM(ReturnType, FunctionName, ParamType1, ParamName1, ParamType2, ParamName2) ReturnType FunctionName (ParamType1 ParamName1, ParamType2 ParamName2) { return m_handler->GetFunction<ReturnType>(#FunctionName, ParamName1, ParamName2) (ParamName1, ParamName2);}
#define DECLARE_LIB_CLASS(ClassName, PublicFunctions) class ClassName{public: DECLARE PublicFunctions;};

#define DECLARE_LIB_CONST_FUNCTION_NO_PARAM(ReturnType, FunctionName) ReturnType FunctionName () const { return m_handler->GetFunction<ReturnType>(#FunctionName) ();}
#define DECLARE_LIB_CONST_FUNCTION_ONE_PARAM(ReturnType, FunctionName, ParamType1, ParamName1) ReturnType FunctionName (ParamType1 ParamName1) const { return m_handler->GetFunction<ReturnType>(#FunctionName, ParamName1) (ParamName1);}
#define DECLARE_LIB_CONST_FUNCTION_TWO_PARAM(ReturnType, FunctionName, ParamType1, ParamName1, ParamType2, ParamName2) ReturnType FunctionName (ParamType1 ParamName1, ParamType2 ParamName2) const { return m_handler->GetFunction<ReturnType>(#FunctionName, ParamName1, ParamName2) (ParamName1, ParamName2);}

#define DECLARE_GLOBLE_LIB_FUNCTION_NO_PARAM(LibName, ReturnType, FunctionName)  ReturnType FunctionName () { return g##LibName->GetFunction<ReturnType>(#FunctionName) ();}
#define DECLARE_GLOBLE_LIB_FUNCTION_ONE_PARAM(LibName, ReturnType, FunctionName, ParamType1, ParamName1) ReturnType FunctionName (ParamType1 ParamName1) { return g##LibName->GetFunction<ReturnType>(#FunctionName, ParamName1) (ParamName1);}
#define DECLARE_GLOBLE_LIB_FUNCTION_TWO_PARAM(LibName, ReturnType, FunctionName, ParamType1, ParamName1, ParamType2, ParamName2) ReturnType FunctionName (ParamType1 ParamName1, ParamType2 ParamName2) { return g##LibName->GetFunction<ReturnType>(#FunctionName, ParamName1, ParamName2) (ParamName1, ParamName2);}

/*! \brief Import the dll function into a class
*	@params name name of the class
*	@params path path from the dll file
*	@params code: declaration (and definition) of the function from the dll file
*/
#define IMPORT_LIB(name, path, code)					\
	class name											\
	{													\
		public:											\
			name()										\
				: m_handler {new SDH::DLLHandler(path)}	\
			{}											\
														\
			~##name()									\
			{											\
				if(m_handler)							\
				{										\
					delete m_handler;					\
					m_handler = nullptr;				\
				}										\
			}											\
			bool IsLibraryValid() const					\
			{											\
				return m_handler->IsLibraryValid();		\
			}											\
														\
			DECLARE code;								\
		private:										\
			SDH::DLLHandler *m_handler;					\
	};


/*! \brief Import the dll functions globally (or in a namespace)
*	@params name name of the class
*	@params path path from the dll file
*	@hint you need to use DECLARE_GLOBLE_LIB_FUNCTION_* to declare and define a function from a DLL file
*/
#define GIMPORT_LIB(name, path) std::unique_ptr<SDH::DLLHandler> g##name (new SDH::DLLHandler(path));
		
		
			

SDH_BEGIN
/*! \brief abstract dll handler implementation
*	use this interface to extent the supported plattforms
*/
class DynamicDLLHandlerImp
{
public:
	virtual ~DynamicDLLHandlerImp ()
	{}
	virtual void LoadHandlerLibrary ( const char* filepath ) = 0;
	virtual void ReleaseHandlerLibrary () = 0;
	virtual void* GetHandlerFunction ( const char* functionName ) const = 0;
	virtual bool IsHandlerLibraryValid () const = 0;
};

/*! \brief user interface to bind dlls
*/
class DLLHandler
{
public:
	DLLHandler ( const char *filepath );
	~DLLHandler ();

	template <typename ReturnType, typename ... Params>
	ReturnType ( *GetFunction ( const char *functionName, Params ... ) ) (Params ...)
	{
		void* fptr = m_impl->GetHandlerFunction ( functionName );
		assert ( fptr );

		return reinterpret_cast<ReturnType ( *) (Params ...)> (fptr);
	}

	bool IsLibraryValid () const;


private:
	DynamicDLLHandlerImp* m_impl;
};
SDH_END
#endif //!DLLHANDLER_H
