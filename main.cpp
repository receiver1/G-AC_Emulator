
#include <windows.h>
#include <chrono>

#include "samp.hpp"
#include "myget.hpp"

unsigned long baseAddress;
struct stSAMP *pSAMP;
bool whileAlive;

std::string generateGuid()
{
	srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
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

	std::string guid = generateGuid();
	std::string nick = getPlayerName();

	std::string query = "/check.php", buffer;
	query += "?N=" + nick;
	query += "&K=" + guid;
	query += "&V=1.0.0.5";
	query += "&I=94.23.111.203:6666";

	MyGet->Init("54.38.11.10");
	MyGet->SendGet(query.c_str(), buffer);

	whileAlive = true;
	while (whileAlive)
	{
		static unsigned long tick = GetTickCount();
		if (GetTickCount() - tick >= 20000)
		{
			query = "/alive.php";
			query += "?N=" + nick;
			query += "&K=" + guid;
			query += "&V=1.0.0.5";
			query += "&I=94.23.111.203:6666";

			MyGet->SendGet(query.c_str(), buffer);

			tick = GetTickCount();
		}
	}
}

class emulator
{
public:
	emulator()
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)main_thread, 0, 0, 0);
	}
	~emulator()
	{
		whileAlive = false;
		MyGet->DeInit();
	}
} _emulator;