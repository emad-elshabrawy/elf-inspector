# ELF Inspector

A lightweight command-line tool written in C for inspecting the internal structure of ELF (Executable and Linkable Format) binaries.

The project was built as a hands-on learning exercise to understand how ELF binaries are organized at the binary level, with a focus on parsing ELF headers, program headers, and section headers directly from the file.

---

## Overview

ELF (Executable and Linkable Format) is the standard binary format used by Linux and many Unix-like systems for executables, object files, shared libraries, and core dumps.

Instead of relying entirely on tools such as `readelf` to display ELF metadata, this project parses selected ELF structures directly in C and presents the extracted information in a simple and readable format.

The current implementation focuses on three major parts of an ELF binary:

```text
ELF Inspector
│
├── ELF Header
│   ├── ELF Class
│   ├── Entry Point
│   ├── Program Header Count
│   └── Section Header Count
│
├── Program Headers
│   ├── Segment Type
│   ├── File Offset
│   ├── Virtual Address
│   ├── File Size
│   ├── Memory Size
│   └── Permissions
│
└── Section Headers
    ├── Section Type
    ├── Address
    ├── File Offset
    └── Size
Features

The current version provides the following functionality:

Parses an ELF64 binary directly from a file.
Displays the ELF class.
Displays the program entry point.
Displays the number of program headers.
Displays the number of section headers.
Parses and displays program header information.
Displays program segment types.
Displays file and virtual memory offsets.
Displays file size and memory size for segments.
Displays segment permissions such as R--, R-X, and RW-.
Parses and displays section header information.
Displays common ELF section types.
Handles GNU ELF versioning section types.
Reports basic file-reading and seeking errors.
How It Works

The program opens the supplied ELF file in binary mode and reads the ELF structures directly using the data structures provided by <elf.h>.

The general parsing flow is:

Input ELF File
      │
      ▼
Open File
      │
      ▼
Read ELF Header
      │
      ├── ELF Class
      ├── Entry Point
      ├── Program Header Count
      └── Section Header Count
      │
      ▼
Read Program Headers
      │
      ├── Segment Type
      ├── Offset
      ├── Virtual Address
      ├── File Size
      ├── Memory Size
      └── Permissions
      │
      ▼
Read Section Headers
      │
      ├── Section Type
      ├── Address
      ├── Offset
      └── Size
      │
      ▼
Display Results

The project intentionally works at the binary-structure level rather than depending on readelf to perform the parsing.

Requirements

The project requires:

Linux or another Unix-like environment with ELF support
GCC
GNU Make
Standard C library
ELF definitions provided by <elf.h>

The project was developed and tested using:

gcc

with the C11 standard.

Building

Clone the repository and enter the project directory:

git clone git@github.com:emad-elshabrawy/elf-inspector.git
cd elf-inspector

Build the project using:

make

Or compile it directly with GCC:

gcc -Wall -Wextra -std=c11 main.c -o elf-inspector
Usage

Run the program by providing an ELF binary as an argument:

./elf-inspector <elf-file>

For example:

./elf-inspector elf-inspector

You can also inspect another ELF executable:

./elf-inspector /bin/ls
Example

Example command:

./elf-inspector elf-inspector

Example output:

ELF Inspector
=============

ELF Class    : ELF64
Entry Point  : 0x10e0
Program Headers : 14
Section Headers : 31

Program Headers
================
[0] PHDR, Offset: 0x40, VirtAddr: 0x40, FileSize: 0x310, MemSize: 0x310, Flags: R--
[1] INTERP, Offset: 0x394, VirtAddr: 0x394, FileSize: 0x1c, MemSize: 0x1c, Flags: R--
[2] LOAD, Offset: 0x0, VirtAddr: 0x0, FileSize: 0x858, MemSize: 0x858, Flags: R--
[3] LOAD, Offset: 0x1000, VirtAddr: 0x1000, FileSize: 0x8a5, MemSize: 0x8a5, Flags: R-X
[4] LOAD, Offset: 0x2000, VirtAddr: 0x2000, FileSize: 0x4dc, MemSize: 0x4dc, Flags: R--
[5] LOAD, Offset: 0x2dd0, VirtAddr: 0x3dd0, FileSize: 0x290, MemSize: 0x2a0, Flags: RW-
[6] DYNAMIC, Offset: 0x2de0, VirtAddr: 0x3de0, FileSize: 0x1e0, MemSize: 0x1e0, Flags: RW-

Section Headers
================
[0] NULL, Address: 0x0, Offset: 0x0, Size: 0x0
[1] NOTE, Address: 0x350, Offset: 0x350, Size: 0x20
[2] NOTE, Address: 0x370, Offset: 0x370, Size: 0x24
[3] PROGBITS, Address: 0x394, Offset: 0x394, Size: 0x1c
[4] GNU_HASH, Address: 0x3b0, Offset: 0x3b0, Size: 0x28
[5] DYNSYM, Address: 0x3d8, Offset: 0x3d8, Size: 0x198
[6] STRTAB, Address: 0x570, Offset: 0x570, Size: 0xcb
[7] VERSYM, Address: 0x63c, Offset: 0x63c, Size: 0x22
[8] VERNEED, Address: 0x660, Offset: 0x660, Size: 0x30
[9] RELA, Address: 0x690, Offset: 0x690, Size: 0xd8
[10] RELA, Address: 0x768, Offset: 0x768, Size: 0xf0
[11] PROGBITS, Address: 0x1000, Offset: 0x1000, Size: 0x17
[12] PROGBITS, Address: 0x1020, Offset: 0x1020, Size: 0xb0
[13] PROGBITS, Address: 0x10d0, Offset: 0x10d0, Size: 0x8
[14] PROGBITS, Address: 0x10e0, Offset: 0x10e0, Size: 0x7bb
[15] PROGBITS, Address: 0x189c, Offset: 0x189c, Size: 0x9
[16] PROGBITS, Address: 0x2000, Offset: 0x2000, Size: 0x35d

The exact addresses and sizes may differ depending on the binary being inspected.

Program Header Information

Program headers describe how different parts of an ELF file are organized for execution.

For each program header, ELF Inspector displays information such as:

Segment Type
Offset
Virtual Address
File Size
Memory Size
Permissions

For example:

[3] LOAD, Offset: 0x1000, VirtAddr: 0x1000,
FileSize: 0x8a5, MemSize: 0x8a5, Flags: R-X

The permission flags indicate whether the corresponding segment is:

R — Readable
W — Writable
X — Executable
Section Header Information

Section headers describe sections contained within the ELF file.

The tool currently displays:

Section Type
Address
File Offset
Size

Examples of section types that may appear include:

NULL
PROGBITS
NOTE
GNU_HASH
DYNSYM
STRTAB
VERSYM
VERNEED
RELA
DYNAMIC
NOBITS
SYMTAB

Unknown section types are reported as:

UNKNOWN
Project Structure
elf-inspector/
│
├── main.c
├── Makefile
├── README.md
├── .gitignore
└── elf-inspector
main.c

Contains the main implementation of the ELF inspection logic, including:

ELF header parsing
Program header parsing
Section header parsing
ELF type mapping
Permission handling
Basic error handling
Makefile

Provides simple build commands for compiling and cleaning the project.

.gitignore

Prevents generated build artifacts and IDE-specific files from being tracked by Git.

README.md

Project documentation, usage instructions, and implementation overview.

Makefile Commands

Build the project:

make

Clean the generated executable:

make clean

A typical workflow is:

make clean
make
./elf-inspector elf-inspector
Learning Objectives

This project was developed primarily as a practical learning exercise.

The main objectives were to understand:

How ELF binaries are structured.
How an ELF header describes a binary.
The difference between program headers and section headers.
How program segments are represented.
How sections are represented.
How file offsets relate to virtual addresses.
How ELF metadata can be parsed directly from a binary file.
How C structures can be used to interpret binary data.
How to work with file operations such as fopen, fread, and fseek.
How to build and organize a small C command-line project using Make.
How to use Git and GitHub for version control and project presentation.
Current Scope

The current implementation intentionally focuses on the core ELF structures needed for this learning exercise.

It currently covers:

ELF64 binaries
ELF header information
Program headers
Section headers
Common segment and section types
Basic segment permission flags

The project does not attempt to reproduce the complete functionality of tools such as readelf.

The scope is intentionally limited so that the underlying ELF structures and parsing process remain understandable and easy to study.

Limitations

The current version is a learning-oriented implementation and therefore has some limitations.

For example:

It focuses on ELF64 structures.
It does not provide the complete feature set of readelf.
It does not aim to fully decode every ELF structure.
Unknown section or program header types may be displayed as UNKNOWN.
The output is intended for readability and learning rather than complete binary analysis.

These limitations are intentional and provide a clear direction for possible future improvements.

Possible Future Improvements

Possible extensions for the project include:

Support for ELF32 binaries.
More detailed ELF header information.
Symbol table inspection.
Dynamic symbol inspection.
String table inspection.
Relocation information.
More detailed section flags.
More detailed program header flags.
Better validation of ELF input files.
More comprehensive error handling.
Command-line options for selecting specific information.
Output formats such as structured or machine-readable output.
Comparison with readelf

This project is inspired by the information exposed by standard ELF analysis tools such as readelf, but it is not intended to replace them.

The main difference is the learning approach:

readelf
   │
   └── Provides a mature and comprehensive ELF inspection utility


ELF Inspector
   │
   └── Focuses on learning how ELF structures can be parsed
       directly from the binary using C

The goal of this project is not to reproduce every feature of readelf, but to understand what is happening underneath such tools.

Error Handling

The program performs basic checks while opening and reading the ELF file.

Errors are reported when operations such as:

Opening the file
Seeking to a file location
Reading ELF structures

fail.

For example:

Error: could not seek to string table header

or:

Failed to read section header
Development Environment

The project was developed as a Linux command-line project using:

Language : C
Standard : C11
Compiler : GCC
Build    : Make
Platform : Linux
Format   : ELF64

Compilation uses:

gcc -Wall -Wextra -std=c11

The project is intentionally kept lightweight and uses standard system facilities for ELF parsing.

Why This Project?

Understanding ELF is an important foundation for low-level Linux development, systems programming, debugging, reverse engineering, and binary analysis.

Rather than only using existing tools to inspect binaries, this project explores how the information can be extracted directly from the ELF file itself.

The project therefore serves as a bridge between:

C Programming
      │
      ▼
Binary File Handling
      │
      ▼
ELF Data Structures
      │
      ▼
Linux Executable Format
      │
      ▼
Binary Analysis Fundamentals
Status

Current status: Functional learning project.

The current implementation successfully parses and displays selected ELF64 header, program header, and section header information.

Further functionality can be added incrementally as understanding of the ELF format develops.

License

This project is currently provided as a personal educational project.

No license has been added at this time
