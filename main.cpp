
#include <windows.h>

#include "myget.hpp"

unsigned long baseAddress;
struct stSAMP *pSAMP;
bool whileAlive;

std::string generateGuid()
{
	std::string template_ = "AAAAAAAA-AAAA-AA-AAAA-AAAAAAAA-AAAA-AAAA-AAAAAAAA";
	for (auto& i : template_)
	{
		if (i == 'A')
		{
			i = char('a' + rand() % ('z' - 'a'));
			srand(i);
		}
	}
	return template_;
}

void main_thread()
{
	do {
		baseAddress = reinterpret_cast<unsigned long>(LoadLibrary("samp.dll"));
	} while (!baseAddress);

	HKEY rKey;
	char Reget[256] = { 0 };
	DWORD RegetPath = sizeof(Reget);
	RegOpenKeyEx(HKEY_CURRENT_USER, "\SOFTWARE\\SAMP", NULL, KEY_QUERY_VALUE, &rKey);
	RegQueryValueEx(rKey, "PlayerName", NULL, NULL, (LPBYTE)&Reget, &RegetPath);

	std::string guid = generateGuid();
	std::string nick = Reget;

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