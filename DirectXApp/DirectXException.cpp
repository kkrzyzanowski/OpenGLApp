#include "DirectXException.h"
#include <sstream>

DirectXException::DirectXException(int line, const char* file) : line(line), file(file)
{
}

const char* DirectXException::GetBufferPointer() const noexcept
{
    std::ostringstream oss;
    oss << GetOriginString();
    Buffer = oss.str();
    return Buffer.c_str();
}

const std::string& DirectXException::GetFile() const noexcept
{
    return file;
}

int DirectXException::GetLine() const noexcept
{
    return line;
}

std::string DirectXException::GetOriginString() const noexcept
{
    std::ostringstream oss;
    oss << "[File] " << file << std::endl << "[Line] " << line;
    return oss.str();
}
