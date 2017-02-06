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
