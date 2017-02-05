#ifndef __cplusplus
#	error C++ compiler required
#endif

#include "DLLHandler.h"

#if defined _WIN32 || defined _WIN64
#	include <Windows.h>
SDH_BEGIN
/*! \brief concrete dll handler implementation
*	use this interface to support mircosoft Windows
*/
class WindowsDLLHandlerImp : public DynamicDLLHandlerImp
{
public:
	void LoadHandlerLibrary(const char* filepath) override
	{
		if (!m_dllHandler)
			m_dllHandler = LoadLibraryA(filepath);
	}
	
	void ReleaseHandlerLibrary() override
	{
		FreeLibrary(m_dllHandler);
		m_dllHandler = nullptr;
	}

	void* GetHandlerFunction(const char* functionName) const override
	{
		return (m_dllHandler) ? reinterpret_cast<void*> (GetProcAddress(m_dllHandler, functionName)) : nullptr;
	}

	bool IsHandlerLibraryValid() const override
	{
		return (m_dllHandler) ? true : false;
	}
private:
	HINSTANCE m_dllHandler;
};
using DynamicDLLHandlerImpType = WindowsDLLHandlerImp;	// WINDOWS DEFINTION
SDH_END
#elif defined __linux__
#	error no linux support yet
#elif defined __APPLE__ || defined __MACH__
#	error no Mac OS X support yet
#else
#	error operating System not supported
#endif

SDH_BEGIN
DLLHandler::DLLHandler(const char * filepath)
	: m_impl{ new DynamicDLLHandlerImpType }
{
	m_impl->LoadHandlerLibrary(filepath);
}

DLLHandler::~DLLHandler()
{
	m_impl->ReleaseHandlerLibrary();
}

bool DLLHandler::IsLibraryValid() const
{
	return m_impl->IsHandlerLibraryValid();
}
SDH_END