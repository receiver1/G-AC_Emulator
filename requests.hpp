#pragma once

#include <windows.h>
#include <wininet.h>
#include <string>

#pragma comment(lib, "wininet")

class cRequests
{
public:
    void init(const char* site, const char* agent);
    void end();
    std::string send(const char* Url);
private:
    HINTERNET hIntSession;
    HINTERNET hHttpSession;
    HINTERNET hHttpRequest;
};