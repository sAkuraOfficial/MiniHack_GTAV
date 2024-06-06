#pragma once // 防止重复引用,删掉会报错.
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
typedef struct ADDRESS
{
    DWORD64 ADDRESS_GLOBAL;
    DWORD64 ADDRESS_WORLD;
    DWORD64 ADDRESS_BLIP;
    DWORD64 ADDRESS_LOCALSCRIPT;
    DWORD64 ADDRESS_TEST;

} ADDRESS;

class memoryContral
{
  public:
    memoryContral();
    memoryContral(LPCSTR name);
    ~memoryContral();
    bool attach();
    MODULEENTRY32 getModule(const std::string &moduleName = "GTA5.exe");
    bool findWindow();
    HWND getWindow();
    void setWindowName(LPCSTR str);
    void initPtr();
    ADDRESS ADDRS;
    LPCSTR m_szWindowName;
    HWND m_hWndTarget;
    HANDLE m_hProc = nullptr;
    template <typename rT>
    inline rT readMem(DWORD64 address)
    {
        rT out;
        if (ReadProcessMemory(m_hProc, (LPVOID)address, &out, sizeof(rT), nullptr))
            return out;
        else
            return NULL;
    }

    template <typename rT>
    inline bool readMem(DWORD64 address, rT *output, DWORD size = NULL, DWORD prot = NULL)
    {
        size = (size == 0) ? sizeof(rT) : size;
        return ReadProcessMemory(m_hProc, (LPVOID)address, output, size, NULL);
    }

    template <typename wT>
    inline bool writeMem(DWORD64 address, wT *value, DWORD size = NULL, DWORD prot = NULL)
    {
        size = (size == 0) ? sizeof(wT) : size;
        return WriteProcessMemory(m_hProc, (LPVOID)address, value, size, NULL);
    }

    template <typename wT>
    inline bool writeMem(DWORD64 address, wT value, DWORD size = NULL, DWORD prot = NULL)
    {
        size = (size == 0) ? sizeof(wT) : size;
        return WriteProcessMemory(m_hProc, (LPVOID)address, &value, size, NULL);
    }

    //    protected:
};
