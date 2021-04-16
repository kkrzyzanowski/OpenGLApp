#include "DirectXWindowException.h"

DirectXWindowException::DirectXWindowException(int line, const char* file, HRESULT hr) : DirectXException(line, file), hr(hr)
{

}

std::string DirectXWindowException::TranslateErrorCode(HRESULT hr)
{
    char* pMsgBuf = nullptr;
    DWORD nMessageLength = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM
        | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPWSTR>(&pMsgBuf), 0, nullptr);
    if (nMessageLength == 0)
    {
        return "Undefined error code";
    }
    std::string errorString = pMsgBuf;
    LocalFree(pMsgBuf);
    return errorString;
}

HRESULT DirectXWindowException::GetErrorCode() const
{
    return hr;
}

std::string DirectXWindowException::GetErrorString() const
{
   return TranslateErrorCode(hr);
}
