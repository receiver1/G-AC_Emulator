
#include <windows.h>
#include <ctime>
#include <thread>

#include "samp.hpp"
#include "requests.hpp"

unsigned long baseAddress;
bool needUnload;

struct stSAMP* pSAMP;
struct HINSTANCE__* hInstance;

std::string generateGuid()
{
	srand(static_cast<unsigned int>(time(NULL)));
	std::string template_ = "AAAAAAAA-AAAA-AA-AAAA-AAAAAAAA-AAAA-AAAA-AAAAAAAA";
	for (auto& i : template_)
	{
		if (i == 'A')
		{
			i = char('a' + rand() % ('z' - 'a'));
		}
	}
	return template_;
}

const char* getPlayerName()
{
	if (pSAMP->pPools->pPlayer == NULL)
		return NULL;

	if (pSAMP->pPools->pPlayer->iLocalPlayerNameAllocated <= 0xF)
		return pSAMP->pPools->pPlayer->szLocalPlayerName;

	return pSAMP->pPools->pPlayer->pszLocalPlayerName;
}

bool isInitializated()
{
	baseAddress = reinterpret_cast<unsigned long>(LoadLibrary("samp.dll"));
	if (!baseAddress)
		return false;

	pSAMP = *reinterpret_cast<stSAMP**>(baseAddress + 0x21A0F8);
	if (!pSAMP)
		return false;

	return true;
}

void main_thread()
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
	}

	while (true)
	{
		Sleep(1);

		if (needUnload)
		{
			request.end();
			FreeLibraryAndExitThread(hInstance, 0);
			break;
		}

		static unsigned long tick = GetTickCount();
		if (GetTickCount() - tick >= 10000)
		{
			query = "/alive.php";
			query += "?N=" + nick;
			query += "&K=" + guid;
			query += "&V=1.0.0.5";
			query += "&I=94.23.111.203:6666";
			request.send(query.c_str());

			tick = GetTickCount();
		}
	}
	ExitThread(0);
}

int __stdcall DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		hInstance = hInstDLL;
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main_thread, 0, 0, 0);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		needUnload = true;
	}
	return 1;
}