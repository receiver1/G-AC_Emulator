
#include <ctime>

#include "samp.hpp"
#include "requests.hpp"

unsigned long baseAddress;
bool needUnload;

struct stSAMP* pSAMP;
struct HINSTANCE__* hInstance;

#include "helpers.hpp"

void threadMain()
{
	while (!isInitializated()) { Sleep(100); }
	while (pSAMP->iGameState != GAMESTATE_AWAIT_JOIN) { Sleep(100); }
	if (strcmp(pSAMP->szIP, "94.23.111.203")) 
	{
		needUnload = true;
	}

	cRequests request;
	request.init("54.38.11.10", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/74.0.3729.169 Safari/537.36");

	std::string query, buffer, guid, nick;
	if (!needUnload)
	{
		guid = generateGuid();
		nick = getPlayerName();

		query = "/check.php";
		query += "?N=" + nick;
		query += "&K=" + guid;
		query += "&V=1.0.0.5";
		query += "&I=94.23.111.203:6666";
		request.send(query.c_str());

		query = "/alive.php";
		query += "?N=" + nick;
		query += "&K=" + guid;
		query += "&V=1.0.0.5";
		query += "&I=94.23.111.203:6666";
	}

	while (true)
	{
		if (needUnload)
		{
			request.end();
			FreeLibraryAndExitThread(hInstance, 0);
			break;
		}

		request.send(query.c_str());

		Sleep(15000ul);
	}
	ExitThread(0);
}

int __stdcall DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		hInstance = hInstDLL;
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(threadMain), 0, 0, 0);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		// Соболезную: из-за задержки в 10 секунд 
		// цикл не успеет выполнить итерацию
		needUnload = true;
	}
	return 1;
}