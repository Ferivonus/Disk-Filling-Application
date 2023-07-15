# Disk Filling Program

This program is designed to fill all available disks on a Windows system with files until they are completely full. It utilizes a buffer size of 1MB for each file and creates multiple files in each directory to occupy the available disk space.

## Prerequisites

To run this program, you need to have the following:

- Windows operating system
- C compiler (e.g., GCC)
- Windows Software Development Kit (SDK) for the required libraries

## Usage

1. Clone or download the source code files to your local machine.

2. Compile the code using a C compiler. For example, using GCC:

```shell
   gcc -o diskfiller.exe diskfiller.c
```

3. Run the compiled executable:

`diskfiller.exe`

4. The program will start filling all available disks with files until they are completely full. It will create files with a 1MB buffer size in each directory, creating multiple files to occupy the disk space.

5. The program will automatically terminate once all disks are filled.

## Disclaimer
Use this program responsibly and with caution. Filling disks with large amounts of data can result in data loss and impact system performance. Make sure you have appropriate permissions before running the program and consider the consequences.

## License
This program is licensed under the MIT License.

