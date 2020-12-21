#pragma once

#include <windows.h>
#include <wininet.h>
#pragma comment(lib,"wininet")
#include <string>

class CMyGet
{
public:
    void Init(const char* site);
    void DeInit();
    void SendGet(const char* Url, std::string& Buffer);
private:
    HINTERNET hIntSession;
    HINTERNET hHttpSession;
    HINTERNET hHttpRequest;
}; 
extern CMyGet* MyGet;