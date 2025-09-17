#include <stdio.h>
#include <windows.h>
#include <winreg.h>
#include <mmsystem.h>
#include <stdio.h>
#include <math.h>
#include <process.h>
#include <stdlib.h>
#include "forge.h"

void *imagine_mutex_create()
{
    CRITICAL_SECTION *mutex;
    mutex = malloc(sizeof *mutex);
    InitializeCriticalSection(mutex);
    return mutex;
}

void imagine_mutex_lock(void *mutex)
{
    EnterCriticalSection(mutex);
}

boolean imagine_mutex_lock_try(void *mutex)
{
    return TryEnterCriticalSection(mutex);
}

void imagine_mutex_unlock(void *mutex)
{
    LeaveCriticalSection(mutex);
}

void imagine_mutex_destroy(void *mutex)
{
    DeleteCriticalSection(mutex);
    free(mutex);
}

void *imagine_signal_create()
{
    HANDLE *p = (HANDLE *)malloc(sizeof(HANDLE));
    if (!p)
        return NULL;
    *p = CreateEvent(NULL, FALSE, FALSE, NULL);
    return p;
}

void imagine_signal_destroy(void *signal)
{
    HANDLE *p = (HANDLE *)signal;
    if (p && *p)
        CloseHandle(*p);
    free(p);
}

boolean imagine_signal_wait(void *signal)
{
    HANDLE *p = (HANDLE *)signal;
    if (!p || !*p)
        return FALSE;
    return WAIT_OBJECT_0 == WaitForSingleObject(*p, INFINITE);
}

boolean imagine_signal_activate(void *signal)
{
    HANDLE *p = (HANDLE *)signal;
    if (!p || !*p)
        return FALSE;
    return SetEvent(*p) ? TRUE : FALSE;
}

typedef struct
{
    void (*func)(void *data);
    void *data;
} ImagineThreadParams;

DWORD WINAPI i_win32_thread(LPVOID param)
{
    ImagineThreadParams *thread_param;
    thread_param = (ImagineThreadParams *)param;
    thread_param->func(thread_param->data);
    //	free(thread_param);
    return TRUE;
}

void imagine_thread(void (*func)(void *data), void *data)
{
    ImagineThreadParams *thread_param;
    thread_param = malloc(sizeof *thread_param);
    thread_param->func = func;
    thread_param->data = data;
    CreateThread(NULL, 0, i_win32_thread, thread_param, 0, NULL);
}

boolean imagine_execute(const char *command)
{
    STARTUPINFO startup_info;
    PROCESS_INFORMATION process_info;
    ZeroMemory(&startup_info, sizeof(startup_info));
    startup_info.cb = sizeof(startup_info);
    ZeroMemory(&process_info, sizeof(process_info));
    return CreateProcess(NULL, (LPSTR)command, NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &process_info);
}
