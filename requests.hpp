#pragma once

#include <windows.h>
#include <wininet.h>
#include <string>

#pragma comment(lib, "wininet")

class cRequests
{
    HINTERNET hIntSession;
    HINTERNET hHttpSession;
    HINTERNET hHttpRequest;
public:
    void init(const char* site, const char* agent);
    void end();
    std::string send(const char* Url);
};