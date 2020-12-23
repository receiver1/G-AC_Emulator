#pragma once

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

const char* generateGuid()
{
	srand(static_cast<unsigned int>(time(NULL)));
	static char templ[50];
	strcpy_s(templ, "AAAAAAAA-AAAA-AA-AAAA-AAAAAAAA-AAAA-AAAA-AAAAAAAA");
	for (auto& i : templ)
	{
		if (i == 'A')
		{
			i = char('a' + rand() % ('z' - 'a'));
		}
	}
	return templ;
}

const char* getPlayerName()
{
	if (pSAMP->pPools->pPlayer == NULL)
		return NULL;

	if (pSAMP->pPools->pPlayer->iLocalPlayerNameAllocated <= 0xF)
		return pSAMP->pPools->pPlayer->szLocalPlayerName;

	return pSAMP->pPools->pPlayer->pszLocalPlayerName;
}