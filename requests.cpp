
#include "requests.hpp"

void cRequests::init(const char* site, const char* agent)
{
    hIntSession = InternetOpenA(agent, INTERNET_OPEN_TYPE_DIRECT, nullptr, nullptr, 0);
    if (hIntSession != nullptr)
        hHttpSession = InternetConnectA(hIntSession, site, INTERNET_DEFAULT_HTTP_PORT, nullptr, nullptr, INTERNET_SERVICE_HTTP, 0, 0);

}
void cRequests::end()
{
    InternetCloseHandle(hHttpRequest);
    InternetCloseHandle(hHttpSession);
    InternetCloseHandle(hIntSession);
}
std::string cRequests::send(const char* Url)
{
    hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", Url, nullptr, nullptr, 0, INTERNET_FLAG_NO_CACHE_WRITE, 0);
    std::string response;
    if (HttpSendRequestA(hHttpRequest, nullptr, 0, nullptr, 0)) {
        char* buf = new char[4096 * 1024];
        DWORD dwBytesRead;
        while (InternetReadFile(hHttpRequest, buf, (4096 * 1024) - 1, &dwBytesRead) && dwBytesRead)
        {
            response.append((char*)buf, dwBytesRead);
        }
        delete[] buf;
    }
    return response;
}

// Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36