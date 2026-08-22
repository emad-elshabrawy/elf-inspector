# ELF Inspector

A lightweight command-line tool written in **C** for inspecting the internal structure of **ELF (Executable and Linkable Format)** binaries on Linux and Unix-like systems.

The project was developed as a hands-on learning exercise focused on understanding how ELF binaries are structured and how their metadata can be parsed directly from the binary file using C.

---

## Overview

ELF is the standard binary format used by Linux and many Unix-like systems for executables, object files, shared libraries, and core dumps.

Instead of relying entirely on tools such as `readelf`, this project parses selected ELF structures directly from the binary file using C and the data structures provided by `<elf.h>`.

The current implementation focuses on three main components:

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
    ├── Virtual Address
    ├── File Offset
    └── Section Size
./elf-inspector /bin/cat

The program prints the ELF header information followed by the program headers and section headers.

Example

Running the program against its own executable:

./elf-inspector elf-inspector

Produces output similar to:

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

The exact values depend on the ELF file being inspected.

Comparison with readelf

The project is intentionally similar in concept to a small subset of the functionality provided by readelf.

For example:

readelf -h <file>

displays ELF header information.

readelf -l <file>

displays program headers.

readelf -S <file>

displays section headers.

The equivalent operation with this project is:

./elf-inspector <file>

The purpose of implementing this functionality manually is educational: the project demonstrates what happens underneath higher-level ELF inspection utilities.

ELF Concepts Covered
ELF Header

The ELF header is located at the beginning of the file and describes fundamental properties of the binary.

Among other fields, it contains information about:

ELF class
Entry point
Location of the program header table
Number of program headers
Location of the section header table
Number of section headers
Program Headers

Program headers describe segments that are relevant to loading and executing the binary.

The project displays information such as:

Type
Offset
Virtual Address
File Size
Memory Size
Flags

The permissions are displayed using:

R = Read
W = Write
X = Execute

For example:

R-X

means the segment is readable and executable.

Section Headers

Section headers describe sections contained within the ELF file.

The project displays:

Section Type
Virtual Address
File Offset
Section Size

Examples of section types encountered include:

PROGBITS
SYMTAB
STRTAB
RELA
DYNAMIC
NOTE
NOBITS
GNU_HASH
Error Handling

The program includes checks around important file operations such as:

Opening the input file
Reading ELF structures
Seeking to file offsets
Reading program headers
Reading section headers

When an operation fails, an error is reported and the file is closed before the program exits.

This is important when dealing with binary files because invalid offsets, corrupted files, truncated files, or unsupported input can otherwise result in incorrect parsing.

Current Scope

The current version focuses on inspecting the main structural metadata of ELF binaries.

The implementation is intentionally kept relatively small and focused on the learning objectives of the project.

It currently demonstrates inspection of:

ELF Header
Program Headers
Section Headers

It is not intended to be a complete replacement for professional ELF analysis tools.

Limitations

This project should be considered a learning-oriented ELF inspector rather than a production-grade binary analysis framework.

Current limitations include:

The implementation is focused on ELF64 structures.
It does not attempt to provide the complete functionality of readelf.
It does not disassemble machine code.
It does not perform symbol resolution analysis.
It does not provide relocation analysis beyond displaying section information.
It does not modify ELF binaries.
It does not provide an interactive interface.
The output is designed for readability and learning rather than machine-readable parsing.

These limitations are intentional and leave room for future improvements.

Possible Future Improvements

Potential extensions to the project include:

Add ELF32 support.
Validate the ELF magic number before parsing.
Display the ELF architecture and machine type.
Display the ELF endianness.
Display the operating system ABI.
Display section names instead of only section types.
Display additional program header metadata.
Display symbol tables.
Display dynamic symbols.
Display relocation entries.
Display string tables.
Add command-line options for selecting specific information.
Add colored terminal output.
Add better validation for malformed or truncated ELF files.
Add support for more ELF architectures.
Add automated tests.
Improve portability across Unix-like systems.
Add structured or machine-readable output.
Learning Outcomes

By implementing this project, the main concepts practiced include:

C
│
├── File I/O
│   ├── fopen()
│   ├── fread()
│   ├── fseek()
│   └── fclose()
│
├── Binary Data
│   ├── Offsets
│   ├── Addresses
│   ├── Sizes
│   └── Hexadecimal representation
│
├── ELF
│   ├── ELF Header
│   ├── Program Headers
│   ├── Section Headers
│   └── ELF Types
│
└── Linux Systems Programming
    ├── Executable Formats
    ├── Memory Segments
    ├── File Layout
    └── Binary Analysis

The project is especially useful as a starting point for understanding how tools such as readelf, binary analysis utilities, and other low-level inspection tools obtain information from executable files.

Development Approach

The implementation intentionally uses the ELF structures available through:

#include <elf.h>

and reads the corresponding structures directly from the binary file.

Rather than depending on a dedicated ELF parsing library, the project works with the underlying file layout and demonstrates the relationship between:

File Offset
     │
     ▼
ELF Structure
     │
     ▼
Parsed Metadata
     │
     ▼
Human-readable Output

This makes the project useful for studying the connection between C structures and real binary file formats.

Building and Testing

A simple development cycle is:

make clean
make
./elf-inspector elf-inspector

The project can also be tested against common Linux executables:

./elf-inspector /bin/ls
./elf-inspector /bin/cat
./elf-inspector /bin/bash

For comparison, the same binaries can be inspected using:

readelf -h /bin/ls
readelf -l /bin/ls
readelf -S /bin/ls

This makes it possible to compare the output of the educational implementation with the corresponding information provided by readelf.

Project Status

Status: Completed — Initial Learning Implementation

The current version successfully demonstrates direct parsing and display of core ELF metadata, including:

ELF header information
Program headers
Section headers
Segment permissions
File offsets
Virtual addresses
File and memory sizes

The project can be extended incrementally as deeper ELF concepts are studied.

Repository

GitHub repository:

https://github.com/emad-elshabrawy/elf-inspector

Author

Emad Elshabrawy

This project was created as a practical systems programming and binary analysis exercise, with the goal of developing a stronger understanding of ELF internals and low-level Linux programming.

License

No license has been specified for this project yet.
