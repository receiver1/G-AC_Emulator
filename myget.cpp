#include "myget.hpp"

CMyGet* MyGet = new CMyGet;

void CMyGet::Init(const char* site)
{
    hIntSession = InternetOpenA("Test", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hIntSession != NULL) hHttpSession = InternetConnectA(hIntSession, site, 80, 0, 0, INTERNET_SERVICE_HTTP, 0, NULL);
}

void CMyGet::DeInit()
{
    InternetCloseHandle(hHttpRequest);
    InternetCloseHandle(hHttpSession);
    InternetCloseHandle(hIntSession);
}

void CMyGet::SendGet(const char* Url, std::string& Buffer)
{
    hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", Url, 0, 0, 0, INTERNET_FLAG_RELOAD, 0);
    const char* szHeaders = "Content-Type: text/html\nMyHeader: Check text"; 
    char szReq[1024] = "";
    HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szReq, strlen(szReq));
    char szBuffer[1025]; 
    unsigned long dwRead = 0;
    while (InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer) - 1, &dwRead) && dwRead)
    {
        szBuffer[dwRead] = 0;
        dwRead = 0;
    }
    Buffer.append(szBuffer, sizeof(szBuffer));
}