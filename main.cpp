
#include <windows.h>
#include <thread>
#include <map>
#include <string>

#include <curl.h>

#include "samp.hpp"
#include "helpers.hpp"

clSAMP samp;

std::map<char, int> offsets
{
	{'1', 0x64}, {'2', 0x67}, {'3', 0x66}, {'4', 0x76}, {'5', 0x75}, {'6', 0x63},
	{'7', 0x62}, {'8', 0x59}, {'9', 0x7A}, {'0', 0x65}, {'-', 0x4B}, {'_', 0x59},
	{'a', 0x77}, {'b', 0x74}, {'c', 0x72}, {'d', 0x71}, {'e', 0x73}, {'f', 0x70},
	{'g', 0x61}, {'h', 0x3F}, {'i', 0x3E}, {'j', 0x6B}, {'k', 0x68}, {'l', 0x3D},
	{'m', 0x6D}, {'n', 0x6E}, {'o', 0x6C}, {'p', 0x40}, {'q', 0x41}, {'r', 0x42},
	{'s', 0x43}, {'t', 0x44}, {'u', 0x45}, {'v', 0x46}, {'w', 0x47}, {'x', 0x4F},
	{'y', 0x49}, {'z', 0x4A}, {'A', 0x53}, {'B', 0x50}, {'C', 0x51}, {'D', 0x56},
	{'E', 0x57}, {'F', 0x54}, {'G', 0x55}, {'H', 0x5A}, {'I', 0x38}, {'J', 0x4B},
	{'K', 0x48}, {'L', 0x58}, {'M', 0x4D}, {'N', 0x4E}, {'O', 0x4C}, {'P', 0x31},
	{'Q', 0x30}, {'R', 0x33}, {'S', 0x32}, {'T', 0x35}, {'U', 0x34}, {'V', 0x37},
	{'W', 0x36}, {'X', 0x3B}, {'Y', 0x3A}, {'Z', 0x39},
};

std::string easy_crypt(std::string input)
{
	for (size_t i{0}; i < input.size(); ++i)
	{
		char glyph = input[i];
		auto it = offsets.find(glyph);
		if (it != offsets.end()) {
			input[i] = static_cast<char>(it->second);
		}
	}
	return input;
}

/*void fast_build(std::string input, std::string compare)
{
	std::map<char, char> out;
	for (size_t i{ 0 }; i < input.size(); ++i)
	{
		auto it = out.find(input[i]);
		if (it != out.end()) {
			continue;
		}

		std::cout << "{\'" << input[i] << "\', 0x" << std::hex << std::uppercase << (uint32_t)compare[i] << "}, " << std::endl;
		out.emplace(input[i], 'a');
	}
}*/

class clEntry
{
	std::thread thread{};
	bool isRunning{true};
public:
	clEntry()
	{
		thread = std::thread([&]()
		{
			while (!samp.isInitializated())
				std::this_thread::sleep_for(std::chrono::milliseconds(100));

			if (strcmp(samp.pInfo->szIP, "46.105.144.50"))
				return;

			// Создаём TextDraw G-AC
			stTextDrawTransmit ts;
			ts.fX = 6.0f;
			ts.fY = 435.0f;
			ts.byteStyle = 1;
			ts.fLetterWidth = 0.204f;
			ts.fLetterHeight = 0.9f;
			ts.fBoxWidth = 398.0f;
			ts.fBoxHeight = 17.0f;
			ts.byteOutline = 1;
			ts.byteShadow = 0;
			ts.dwLetterColor = -76;
			ts.dwBackgroundColor = 0x4D4D4D50;
			ts.dwBoxColor = 50;
			ts.byteFlags = 1;

			samp.createTextdraw(1337, &ts, "G-AC");

			char query[256], header[256], guid[128], nick[24];

			strcpy_s(guid, generateGuid());
			strcpy_s(nick, samp.getPlayerName());

			CURL* curl = curl_easy_init();
			sprintf_s(query, "https://avt.g-ac.su/check.php?IDI=%s&NA=%s"
				"&XU=1.0.0.6&Y=46.105.144.50:6666", nick, guid);

			curl_easy_setopt(curl, CURLOPT_URL, query);
			curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
				"AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.88 Safari/537.36 OPR/73.0.3856.284");
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

			struct curl_slist* headers{ 0 };
			sprintf_s(header, "IDI: %s", easy_crypt(nick).c_str());
			headers = curl_slist_append(headers, header);
			sprintf_s(header, "NA: %s", easy_crypt(guid).c_str());
			headers = curl_slist_append(headers, header);
			headers = curl_slist_append(headers, "XU: 1.0.0.6");
			headers = curl_slist_append(headers, "Y: vc8deu8dvv8ueicccc");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

			curl_easy_perform(curl);

			while (isRunning)
			{
				sprintf_s(query, "https://avt.g-ac.su/alive.php?IDI=%s&NA=%s"
					"&XU=1.0.0.6&Y=46.105.144.50:6666", nick, guid);

				curl_easy_setopt(curl, CURLOPT_URL, query);
				curl_easy_perform(curl);

				std::this_thread::sleep_for
				(std::chrono::milliseconds(5000));
			}
			curl_easy_cleanup(curl);
			curl_slist_free_all(headers);
		});
		thread.detach();
	}
} entry;
