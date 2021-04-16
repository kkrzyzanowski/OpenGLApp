#pragma once
#include <exception>
#include <string>
class DirectXException :public std::exception
{
public:
	DirectXException(int line, const char* file);
	const char* GetBufferPointer() const noexcept;
	const std::string& GetFile() const noexcept;
	int GetLine() const noexcept;
	std::string GetOriginString() const noexcept;
private:
	int line;
	std::string file;
protected: 
	mutable std::string Buffer;

};

