#include <Windows.h>
#include <thread>
#pragma comment(lib, "winmm.lib")
typedef union _RGBQUAD {
    COLORREF rgb;
    struct {
        BYTE r;
        BYTE g;
        BYTE b;
        BYTE Reserved;
    };
}_RGBQUAD, * PRGBQUAD;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) {
    if (red != length) {
        red < length; red++;
        if (ifblue == true) {
            return RGB(red, 0, length);
        }
        else {
            return RGB(red, 0, 0);
        }
    }
    else {
        if (green != length) {
            green < length; green++;
            return RGB(length, green, 0);
        }
        else {
            if (blue != length) {
                blue < length; blue++;
                return RGB(0, length, blue);
            }
            else {
                red = 0; green = 0; blue = 0;
                ifblue = true;
            }
        }
    }
}
DWORD WINAPI Cursors(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    RECT rect;
    GetWindowRect(GetDesktopWindow(), &rect);
    int w = rect.right - rect.left;
    int h = rect.bottom - rect.top;
    HDC hdcDesktop = GetDC(GetDesktopWindow());

    for (int t = 0;; t++)
    {
        CURSORINFO curInf = { sizeof(CURSORINFO) };
        if (GetCursorInfo(&curInf) && curInf.hCursor)
        {
            int spawnCount = (rand() % 6) + 1;
            for (int i = 0; i < spawnCount; i++)
            {
                int x = rand() % (w - GetSystemMetrics(SM_CXCURSOR) + 1);
                int y = rand() % (h - GetSystemMetrics(SM_CYCURSOR) + 1);
                DrawIcon(hdcDesktop, x, y, curInf.hCursor);
            }
            DestroyCursor(curInf.hCursor);
        }
        Sleep(rand() % 8 + 3);
    }
    ReleaseDC(GetDesktopWindow(), hdcDesktop);
    return 0;
}
DWORD WINAPI pacman1(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(0);
		int y = GetSystemMetrics(1);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
		SelectObject(hdc, brush);
		Pie(hdc, rand() % x, rand() % y, rand() % x, rand() % y, rand() % x, rand() % y, rand() % x, rand() % y);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
		//Sleep(10);
	}
}
DWORD WINAPI shader1(LPVOID lpParam) {
	HDC hdcScreen = GetDC(0), hdcMem = CreateCompatibleDC(hdcScreen);
	INT w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	BITMAPINFO bmi = { 0 };
	PRGBQUAD rgbScreen = { 0 };
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biWidth = w;
	bmi.bmiHeader.biHeight = h;
	HBITMAP hbmTemp = CreateDIBSection(hdcScreen, &bmi, NULL, (void**)&rgbScreen, NULL, NULL);
	SelectObject(hdcMem, hbmTemp);
	for (;;) {
		hdcScreen = GetDC(0);
		BitBlt(hdcMem, 0, 0, w, h, hdcScreen, 0, 0, SRCCOPY);
		for (INT i = 0; i < w * h; i++) {
			INT x = i % w, y = i / w;
			rgbScreen[i].rgb += x + y;
		}
		BitBlt(hdcScreen, 0, 0, w, h, hdcMem, 0, 0, SRCCOPY);
		ReleaseDC(NULL, hdcScreen); DeleteDC(hdcScreen);
	}
}
DWORD WINAPI shader2(LPVOID lpParam) {
    int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
    double moveangle = 0;
    while (1) {
        HDC hdc = GetDC(0);
        SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
        int rx = rand() % sw;
        int ry = rand() % sh;
        BitBlt(hdc, 10, ry, sw, 96, hdc, 0, ry, 0x1900ac010e);
        BitBlt(hdc, -10, ry, sw, -96, hdc, 0, ry, 0x1900ac010e);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}
DWORD WINAPI RanTunnel(LPVOID lpParam) {
    HDC hdc = GetDC(0);
    int sw = GetSystemMetrics(0);
    int sh = GetSystemMetrics(1);
    while (true)
    {
        hdc = GetDC(0);
        StretchBlt(hdc, 0, 0, rand() % sw, rand() % sh, hdc, 0, 0, sw, sh, SRCCOPY);
        ReleaseDC(GetDesktopWindow(), hdc);
        DeleteDC(hdc);
        Sleep(100);
    }
}
DWORD WINAPI train(LPVOID lpParam) {
    int w = GetSystemMetrics(0);
    int h = GetSystemMetrics(1);
    while (1) {
        HDC hdc = GetDC(0);
        BitBlt(hdc, -60, 0, w, h, hdc, 0, 0, SRCCOPY);
        BitBlt(hdc, w - 60, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
        ReleaseDC(0, hdc);
        Sleep(10);
    }
}
VOID WINAPI sound1() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((((t / 2 * (4 | t >> 13 & 3) >> (~t >> 11 & 1) | ~t >> 5) & 127) + (t * (t >> 11 & t >> 13) * (~t >> 9 & 3) & 127) / 2 + ((t & 4096 ? (t * (t ^ t % 255) | t >> 5) >> 1 : t >> 4 | (t & 8192 ? t << 1 : t)) & 127) + 64));

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 40] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((((t * (t & 16384 ? 7 : 5) * (3 - (3 & t >> 9) + (3 & t >> (-t >> 20 & 1 ? 8 : 11))) >> (3 & -t >> (t & (-t & 57344 ? 4096 : 6144) ? 2 : 16)) | (-t & 24576 ? (3 * t >> 5) % 192 : (t >> 4) % 192) | (t >> 20 & 1 ? t >> 4 : t >> (-t >> 18 & 1) + 2)) & 255) >> 1) - (t >> 18 & 1 ? ((-t >> 1) * (t & 16384 ? 7 : 5) >> (-t >> 10 & 3) & t >> 4 & 255) >> 1 : (-t >> 2) * (t & 16384 ? 7 : 5) >> (-t >> 10 & 3) & (t >> 4 & 255) >> 1) + (128 & (int)(4E4 / (1 + (t & (-t & 28672 ? 4095 : 2047))))) + (t >> 18 & 3 && -(t * (t ^ t % 9) & 255 & -(t >> (t >> 11 & 31 ? (-t & 14336 ? 5 : 4) - !(-t & 28672) - !(-t & 122880) : 6)) << 2 & 255) >> 2) + 128);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t >> 6 | t << 1) + (t >> 5 | t << 3 | t >> 3) | t >> 2 | t << 1);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[8000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((2 * t & 255) * (-t >> 6 & 255) >> 8);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
    HWAVEOUT hWaveOut = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
    waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[11025 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t * (t & 8192 ? 7 : 5) * (6 - (3 & t >> 8) + (3 & t >> 9)) >> (3 & -t >> (t & 2048 ? 2 : 11)) | t >> 3);

    WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
    waveOutClose(hWaveOut);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

    if (MessageBoxW(NULL, L"rnq.exe, This program contains GDI\r\n\Run it?", L"rnq.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
    {
        ExitProcess(0);
    }
    else
    {
        if (MessageBoxW(NULL, L"Final chance to stop this program.", L"rnq.exe", MB_YESNO | MB_ICONEXCLAMATION) == IDNO)
        {
            ExitProcess(0);
        }
        else
        Sleep(5000);
        HANDLE T1 = CreateThread(NULL, 0, Cursors, NULL, 0, NULL);
        sound1();
        Sleep(30000);
        Sleep(5000);
        TerminateThread(T1, 0);
        CloseHandle(T1);
        Sleep(1000);
        HANDLE T2 = CreateThread(NULL, 0, shader1, NULL, 0, NULL);
        sound2();
        Sleep(40000);
        TerminateThread(T2, 0);
        CloseHandle(T2);
        Sleep(1000);
        HANDLE T3 = CreateThread(NULL, 0, shader2, NULL, 0, NULL);
        sound3();
        Sleep(30000);
        TerminateThread(T3, 0);
        CloseHandle(T3);
        Sleep(1000);
        HANDLE T4 = CreateThread(NULL, 0, RanTunnel, NULL, 0, NULL);
        sound4();
        Sleep(30000);
        TerminateThread(T4, 0);
        CloseHandle(T4);
        Sleep(1000);
        HANDLE T5 = CreateThread(NULL, 0, train, NULL, 0, NULL);
        sound5();
	Sleep(30000);
    }
}