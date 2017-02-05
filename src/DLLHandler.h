#ifndef DLLHANDLER_H
#define DLLHANDLER_H
#pragma once
#include <assert.h>

#ifndef FLS_GLOABLE
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

#define IMPORT_LIB(name, path, code)					\
	class name											\
	{													\
		public:											\
			name()										\
				: m_handler {new FLS::DLLHandler(path)}	\
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
			FLS::DLLHandler *m_handler;					\
	};

SDH_BEGIN
/*! \brief abstract dll handler implementation
*	use this interface to extent the supported plattforms
*/
class DynamicDLLHandlerImp
{
public:
	virtual ~DynamicDLLHandlerImp() {}
	virtual void LoadHandlerLibrary(const char* filepath) = 0;
	virtual void ReleaseHandlerLibrary() = 0;
	virtual void* GetHandlerFunction(const char* functionName) const = 0;
	virtual bool IsHandlerLibraryValid() const = 0;
};

/*! \brief user interface to bind dlls
*/
class DLLHandler
{
public:
	DLLHandler(const char *filepath);
	~DLLHandler();

	template <typename ReturnType, typename ... Params>
	ReturnType(*GetFunction(const char *functionName, Params ...)) (Params ...)
	{
		void* fptr = m_impl->GetHandlerFunction ( functionName );
		assert ( fptr );

		return reinterpret_cast<ReturnType ( *) (Params ...)> (fptr);
	}

	bool IsLibraryValid() const;


private:
	DynamicDLLHandlerImp* m_impl;
};
SDH_END

#endif //!DLLHANDLER_H

