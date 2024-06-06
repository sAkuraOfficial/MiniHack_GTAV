#include "memory.h"
#include "patternBatch.hpp"

memoryContral::memoryContral()
{
}

memoryContral::memoryContral(LPCSTR name)
{
    m_szWindowName = name;
}

memoryContral::~memoryContral()
{
    CloseHandle(m_hProc);
}

bool memoryContral::attach()
{
    if (m_hProc != nullptr)
        return 1;

    if (!this->findWindow())
        return 0;

    DWORD dwProcId;
    GetWindowThreadProcessId(m_hWndTarget, &dwProcId);
    if (!dwProcId)
        return 0;

    auto a = PROCESS_ALL_ACCESS;
    m_hProc = OpenProcess(
        PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_QUERY_INFORMATION, 0, dwProcId
    );
    if (m_hProc == nullptr)
        return 0;
    initPtr();

    return 1;
}

MODULEENTRY32 memoryContral::getModule(const std::string &moduleName)
{
    DWORD dwProcId;
    GetWindowThreadProcessId(m_hWndTarget, &dwProcId);

    HANDLE hModuleSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcId);
    MODULEENTRY32 mEntry;

    if (hModuleSnapshot == INVALID_HANDLE_VALUE)
        return MODULEENTRY32();

    mEntry.dwSize = sizeof(mEntry);

    if (!Module32First(hModuleSnapshot, &mEntry))
        CloseHandle(hModuleSnapshot);

    do
    {
        if (std::string(mEntry.szModule) == moduleName)
            return mEntry;
    } while (Module32Next(hModuleSnapshot, &mEntry));

    CloseHandle(hModuleSnapshot);
    return MODULEENTRY32();
}

bool memoryContral::findWindow()
{
    m_hWndTarget = FindWindow(nullptr, m_szWindowName);
    if (!m_hWndTarget)
        return 0;
    return 1;
}

HWND memoryContral::getWindow()
{
    return m_hWndTarget;
}

void memoryContral::setWindowName(LPCSTR str)
{
    m_szWindowName = str;
}

void memoryContral::initPtr()
{
    auto base = getModule();

    auto rip = [&](DWORD64 offset) {
        return readMem<int>((DWORD64)base.modBaseAddr + offset + 3) + 7 + offset;
    }; // 这里必须要以int方式读取,不然会出错

    auto rip2 = [&](DWORD64 offset) {
        return readMem<int>((DWORD64)base.modBaseAddr + offset + 14) + 735 + offset;
    }; // 这里必须要以int方式读取,不然会出错

    patternBatch patternMain(base, this);

    patternMain.add("World", "48 8B 05 ? ? ? ? 45 ? ? ? ? 48 8B 48 08 48 85 C9 74 07", [&](DWORD64 offset) {
        ADDRS.ADDRESS_WORLD = rip(offset);
    });

    patternMain.add("TEST", "E8 ? ? ? ? 8B 0D ? ? ? ? 40 38 3D ? ? ? ?", [&](DWORD64 offset) {
        ADDRS.ADDRESS_TEST = rip2(offset);
    });

    patternMain.add("Blip", "4C 8D 05 ? ? ? ? 0F B7 C1", [&](uintptr_t offset) {
        ADDRS.ADDRESS_BLIP = rip(offset);
    });

    patternMain.add("Global", "4C 8D 05 ? ? ? ? 4D 8B 08 4D 85 C9 74 11", [&](uintptr_t offset) {
        ADDRS.ADDRESS_GLOBAL = rip(offset);
    });
    patternMain.add("LocalScript", "48 8B 05 ? ? ? ? 8B CF 48 8B 0C C8 39 59 68", [&](uintptr_t offset) {
        ADDRS.ADDRESS_LOCALSCRIPT = rip(offset);
    });
    patternMain.run();
}
