# ELF Inspector

A lightweight command-line tool written in C for inspecting the internal
structure of ELF (Executable and Linkable Format) binaries.

The project was built as a hands-on learning exercise to understand how
ELF binaries are organized at the binary level, with a focus on parsing
ELF headers, program headers, and section headers directly from the file.

---

## Overview

ELF is the standard binary format used by Linux and many Unix-like systems
for executables, object files, shared libraries, and core dumps.

Instead of relying on tools such as `readelf` to display ELF metadata,
this project parses the ELF structures directly in C and presents selected
information in a simple and readable format.

The current implementation focuses on three major parts of an ELF binary:

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

---

## Features

### ELF Header

The tool reads the ELF header and displays basic information about the
binary, including:

- ELF class
- Entry point address
- Number of program headers
- Number of section headers

Example:

ELF Class    : ELF64
Entry Point  : 0x10e0
Program Headers : 14
Section Headers : 31

---

### Program Headers

Program headers describe how parts of an ELF file are mapped into memory
when the executable is loaded.

The inspector displays:

- Program header index
- Segment type
- File offset
- Virtual address
- File size
- Memory size
- Segment permissions

Example:

[2] LOAD, Offset: 0x0, VirtAddr: 0x0,
    FileSize: 0x858, MemSize: 0x858, Flags: R--

[3] LOAD, Offset: 0x1000, VirtAddr: 0x1000,
    FileSize: 0x8a5, MemSize: 0x8a5, Flags: R-X

[5] LOAD, Offset: 0x2dd0, VirtAddr: 0x3dd0,
    FileSize: 0x290, MemSize: 0x2a0, Flags: RW-

Known program header types are translated into human-readable names such
as:

PHDR
INTERP
LOAD
DYNAMIC
NOTE
GNU_PROPERTY
GNU_EH_FRAME
GNU_STACK
GNU_RELRO

Unknown types are reported as `UNKNOWN` rather than being silently ignored.

---

### Section Headers

Section headers describe the logical sections contained within an ELF file.

The inspector displays:

- Section index
- Section type
- Virtual address
- File offset
- Section size

Example:

[11] PROGBITS, Address: 0x1000, Offset: 0x1000, Size: 0x17
[14] PROGBITS, Address: 0x10e0, Offset: 0x10e0, Size: 0x7bb
[22] DYNAMIC, Address: 0x3de0, Offset: 0x2de0, Size: 0x1e0
[28] SYMTAB, Address: 0x0, Offset: 0x3080, Size: 0x498

The implementation recognizes several standard and GNU-specific section
types, including:

NULL
PROGBITS
SYMTAB
STRTAB
RELA
DYNAMIC
NOTE
NOBITS
GNU_HASH
DYNSYM
VERSYM
VERNEED

---

## Example

Running the inspector against itself:

./elf-inspector elf-inspector

produces output similar to:

ELF Inspector
=============

ELF Class    : ELF64
Entry Point  : 0x10e0
Program Headers : 14
Section Headers : 31

Program Headers
================
[0] PHDR, Offset: 0x40, VirtAddr: 0x40,
    FileSize: 0x310, MemSize: 0x310, Flags: R--

[1] INTERP, Offset: 0x394, VirtAddr: 0x394,
    FileSize: 0x1c, MemSize: 0x1c, Flags: R--

[2] LOAD, Offset: 0x0, VirtAddr: 0x0,
    FileSize: 0x858, MemSize: 0x858, Flags: R--

[3] LOAD, Offset: 0x1000, VirtAddr: 0x1000,
    FileSize: 0x8a5, MemSize: 0x8a5, Flags: R-X

[5] LOAD, Offset: 0x2dd0, VirtAddr: 0x3dd0,
    FileSize: 0x290, MemSize: 0x2a0, Flags: RW-

Section Headers
================
[0] NULL, Address: 0x0, Offset: 0x0, Size: 0x0
[1] NOTE, Address: 0x350, Offset: 0x350, Size: 0x20
[4] GNU_HASH, Address: 0x3b0, Offset: 0x3b0, Size: 0x28
[5] DYNSYM, Address: 0x3d8, Offset: 0x3d8, Size: 0x198
[14] PROGBITS, Address: 0x10e0, Offset: 0x10e0, Size: 0x7bb
[22] DYNAMIC, Address: 0x3de0, Offset: 0x2de0, Size: 0x1e0
[26] NOBITS, Address: 0x4060, Offset: 0x3060, Size: 0x10
[28] SYMTAB, Address: 0x0, Offset: 0x3080, Size: 0x498

---

## Building

### Requirements

The project requires:

- GCC
- GNU Make
- A Linux/Unix-like environment
- Standard C11 compiler support

On Kali Linux, the required build tools are normally available through
the standard development environment.

---

### Build with Make

Clone the repository and enter the project directory:

git clone https://github.com/<your-username>/elf-inspector.git
cd elf-inspector

Build the project:

make

This creates:

elf-inspector

---

### Manual Compilation

The program can also be compiled directly with GCC:

gcc -Wall -Wextra -std=c11 main.c -o elf-inspector

The compiler flags enable useful warnings and enforce the C11 standard:

- `-Wall` — enable common compiler warnings
- `-Wextra` — enable additional warnings
- `-std=c11` — compile using the C11 language standard

---

## Usage

The program expects an ELF file as a command-line argument:

./elf-inspector <elf-file>

For example:

./elf-inspector elf-inspector

You can also inspect another ELF executable available on your system:

./elf-inspector /bin/ls

---

## Cleaning the Build

To remove the generated executable:

make clean

The generated binary is intentionally excluded from version control through
`.gitignore`.

---

## Project Structure

elf-inspector/
│
├── main.c
│   └── ELF parsing and inspection logic
│
├── Makefile
│   └── Build and cleanup commands
│
├── README.md
│   └── Project documentation
│
├── .gitignore
│   └── Files excluded from Git
│
└── elf-inspector
    └── Generated executable (not tracked by Git)

---

## How It Works

At a high level, the program follows this process:

                    ELF File
                       │
                       ▼
              Read ELF Header
                       │
          ┌────────────┴────────────┐
          │                         │
          ▼                         ▼
   Program Headers           Section Headers
          │                         │
          ▼                         ▼
   Parse each segment        Parse each section
          │                         │
          ▼                         ▼
   Decode type/flags         Decode section type
          │                         │
          └────────────┬────────────┘
                       │
                       ▼
                Human-readable
                     output

The implementation uses the ELF data structures provided by the system
headers and reads the binary metadata directly rather than invoking
`readelf` internally.

---

## ELF Concepts Covered

This project provides practical exposure to several important ELF concepts:

### ELF Header

The ELF header acts as the main metadata structure of the binary.

It contains information that allows the program to determine how the rest
of the ELF file should be interpreted.

---

### Program Headers

Program headers describe the parts of the file that are relevant to the
runtime loader.

They are especially important for understanding how an executable is
mapped into memory.

For example, a typical executable contains different `LOAD` segments with
different permissions:

R--   Read-only
R-X   Read + Execute
RW-   Read + Write

---

### Section Headers

Sections organize the contents of the ELF file into logical units.

Common examples include:

.text
.rodata
.data
.bss
.symtab
.strtab
.dynsym
.dynstr
.rela.dyn
.rela.plt

The inspector currently focuses on their metadata rather than dumping the
contents of each section.

---

## Design Goals

The project was intentionally kept small and focused.

The main goals are:

1. Understand the structure of ELF binaries.
2. Practice binary file parsing in C.
3. Work with ELF structures and fixed-width integer types.
4. Understand the difference between program headers and section headers.
5. Convert low-level numeric constants into human-readable information.
6. Build a useful command-line utility without depending on external ELF
   inspection tools for its core functionality.
7. Practice writing portable, warning-clean C code within the supported
   environment.

---

## Current Scope

The current version focuses on inspecting ELF metadata.

It currently provides information about:

- ELF class
- Entry point
- Program header count
- Section header count
- Program header types
- Program header offsets
- Program header virtual addresses
- Program header file sizes
- Program header memory sizes
- Program header permissions
- Section types
- Section addresses
- Section offsets
- Section sizes

The project is intentionally not a full replacement for `readelf`.

---

## Future Improvements

Possible future improvements include:

- Displaying ELF endianness
- Displaying machine architecture
- Displaying ELF file type
- Displaying ELF version information
- Displaying section names
- Displaying section flags
- Displaying section alignment
- Displaying program header alignment
- Showing the ELF interpreter
- Displaying symbol tables
- Displaying dynamic symbols
- Displaying relocation entries
- Displaying section-to-segment mappings
- Adding stronger input validation
- Improving error messages
- Supporting additional ELF classes and architectures
- Adding more detailed command-line options

These features are intentionally left as future work so the project can
evolve incrementally.

---

## Learning Outcomes

Building this project provided practical experience with:

- C programming
- Binary file parsing
- ELF file structures
- Linux executable formats
- Memory addresses and file offsets
- Program loading concepts
- File I/O
- Structures and fixed-width data types
- Bitwise flags
- Command-line arguments
- GCC compiler warnings
- Makefiles
- Git and GitHub workflow

---

## Validation

The output of the tool can be compared against established Linux ELF
inspection utilities such as:

readelf -h <file>
readelf -l <file>
readelf -S <file>

For example:

./elf-inspector elf-inspector
readelf -h elf-inspector
readelf -l elf-inspector
readelf -S elf-inspector

The purpose of this comparison is to validate the parsed ELF metadata and
better understand how the information displayed by standard ELF utilities
maps to the underlying ELF structures.

---

## License

This project is provided for educational and learning purposes.

A specific open-source license can be added in a future revision.
