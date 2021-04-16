#pragma once
#include <Windows.h>
#include "DirectXException.h"

#define CHWND_EXCEPT(hr) DirectXWindowException(__LINE__, __FILE__, hr);

class DirectXWindowException :
    public DirectXException
{
    DirectXWindowException(int line, const char* file, HRESULT hr);
    static std::string TranslateErrorCode(HRESULT hr);
    HRESULT GetErrorCode() const;
    std::string GetErrorString() const;
private:
    HRESULT hr;
};
