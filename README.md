# ELF Inspector

### A Lightweight ELF Binary Analysis Tool Built in C

> **ELF Inspector** is a command-line utility that parses ELF binaries directly and transforms low-level executable metadata into clear, human-readable information.

---

## 📌 Overview

**ELF (Executable and Linkable Format)** is one of the fundamental binary formats used by Linux and Unix-like systems. It is used for executables, object files, shared libraries, and core dumps.

Although compiled programs are normally treated as ready-to-run applications, an ELF binary contains a structured representation that describes how the file should be interpreted and, for executable files, how relevant parts are loaded into memory.

**ELF Inspector** explores this structure from the binary level.

Instead of relying on `readelf` internally, the project reads the ELF file directly in **C**, interprets its metadata, and presents the most important information in a compact and readable command-line output.

The current implementation focuses on three fundamental components:

```text
                         ELF Binary
                             │
                             ▼
                      ┌─────────────┐
                      │ ELF Header  │
                      └──────┬──────┘
                             │
                 ┌───────────┴───────────┐
                 ▼                       ▼
        Program Header Table     Section Header Table
                 │                       │
                 ▼                       ▼
          Runtime / Loading       Logical Organization
              Metadata                Metadata
                 │                       │
                 └───────────┬───────────┘
                             ▼
                    Human-readable Output
```
Project Purpose

The main purpose of ELF Inspector is to make the internal structure of an ELF binary understandable through a practical systems-programming implementation.

The project connects several important concepts:

C Programming → Binary File I/O → ELF Structures → Memory & Addresses → Program Loading → Executable Analysis

Rather than simply using an existing ELF inspection tool, the project demonstrates how the underlying metadata can be accessed and interpreted programmatically.

🔍 What Does It Inspect?
1. ELF Header

The ELF Header acts as the starting point for interpreting the binary.

ELF Inspector extracts:

ELF Class — such as ELF64
Entry Point Address
Number of Program Headers
Number of Section Headers

For example:

ELF Class        : ELF64
Entry Point      : 0x10e0
Program Headers  : 14
Section Headers  : 31

The entry point is particularly important because it represents the virtual address where execution begins for an executable.

2. Program Headers

Program Headers describe segments and provide information relevant to the runtime loading of an ELF file.

For each program header, the inspector reports:

Segment index
Segment type
File offset
Virtual address
File size
Memory size
Permissions

Example:

[2] LOAD, Offset: 0x0, VirtAddr: 0x0,
    FileSize: 0x858, MemSize: 0x858, Flags: R--

[3] LOAD, Offset: 0x1000, VirtAddr: 0x1000,
    FileSize: 0x8a5, MemSize: 0x8a5, Flags: R-X

[5] LOAD, Offset: 0x2dd0, VirtAddr: 0x3dd0,
    FileSize: 0x290, MemSize: 0x2a0, Flags: RW-

Recognized segment types are converted from numeric ELF constants into meaningful names such as:

PHDR, INTERP, LOAD, DYNAMIC, NOTE, GNU_PROPERTY, GNU_EH_FRAME, GNU_STACK, and GNU_RELRO.

Segment permissions are also represented in a readable form:

R--   Read
R-X   Read + Execute
RW-   Read + Write

This makes the Program Header table useful for understanding how different parts of an executable relate to memory and execution.

3. Section Headers

Section Headers describe the logical organization of an ELF file.

The inspector reports:

Section index
Section type
Virtual address
File offset
Section size

Example:

[11] PROGBITS, Address: 0x1000, Offset: 0x1000, Size: 0x17
[14] PROGBITS, Address: 0x10e0, Offset: 0x10e0, Size: 0x7bb
[22] DYNAMIC,  Address: 0x3de0, Offset: 0x2de0, Size: 0x1e0
[28] SYMTAB,   Address: 0x0,    Offset: 0x3080, Size: 0x498

The project focuses on section metadata, rather than dumping the complete raw contents of every section.

🧠 Program Headers vs. Section Headers

One of the key concepts demonstrated by the project is that Program Headers and Section Headers describe the ELF file from two different perspectives.

Program Headers	Section Headers
Describe segments	Describe sections
Runtime / loading perspective	Logical / organizational perspective
Important to the loader	Important for linking and organization
Focus on memory mapping	Focus on file organization

A useful mental model is:

Program Headers  →  How is it loaded?

Section Headers  →  How is it organized?

Understanding this distinction is central to understanding ELF internals.

⚙️ How ELF Inspector Works

The tool follows a direct parsing workflow:
```text
             Input ELF File
                    │
                    ▼
              Read ELF Header
                    │
          ┌─────────┴─────────┐
          ▼                   ▼
   Program Headers      Section Headers
          │                   │
          ▼                   ▼
    Parse Segments       Parse Sections
          │                   │
          ▼                   ▼
    Decode Types          Decode Types
    & Permissions             │
          │                   │
          └─────────┬─────────┘
                    ▼
            Formatted Output
```
The implementation works directly with ELF structures provided by the system headers and reads the binary metadata itself.

readelf is not used internally by the core parser.

🛠️ Key Design Decisions
Direct Binary Parsing

The project intentionally parses the ELF file directly instead of executing an external inspection utility.

This keeps the implementation close to the actual representation of the ELF format.

Human-readable Metadata

ELF structures contain many numeric constants. Displaying only raw numbers would make the output difficult to interpret.

Therefore, recognized values are translated into meaningful names such as:

LOAD
PHDR
INTERP
DYNAMIC
NOTE
PROGBITS
SYMTAB
DYNSYM
Explicit Unknown Handling

If an ELF type is not recognized by the current implementation, it is reported as:

UNKNOWN

Rather than silently ignoring unsupported values, the tool makes the limitation visible. This improves transparency during analysis and debugging.

Focused Command-Line Interface

The tool follows a simple interface:

./elf-inspector <elf-file>

This keeps the utility lightweight and makes it easy to test against different ELF binaries.

🚀 Getting Started
Requirements
Linux / Unix-like environment
GCC
GNU Make
An ELF binary to inspect
Build
make
Run
./elf-inspector <elf-file>

For example:

./elf-inspector /bin/ls

You can also compile a small C program and inspect the resulting executable:

gcc hello.c -o hello
./elf-inspector hello
Clean
make clean
🧪 Validation

Correctness is an important part of a binary parser.

To validate the implementation, the same ELF binary can be inspected using both ELF Inspector and the standard Linux readelf utility.

ELF Header
./elf-inspector elf-inspector
readelf -h elf-inspector
Program Headers
readelf -l elf-inspector
Section Headers
readelf -S elf-inspector

The outputs can be compared using values such as:

ELF class
Entry point
Program header count
Section header count
Segment types
File offsets
Virtual addresses
File sizes
Memory sizes
Permissions
Section types
Section sizes

The objective is not to reproduce the entire readelf feature set, but to verify that the metadata parsed by ELF Inspector corresponds to the relevant ELF information reported by an established reference utility.

📦 Current Scope

The current version provides inspection of:

ELF Header

ELF class
Entry point
Program header count
Section header count

Program Headers

Segment index
Segment type
File offset
Virtual address
File size
Memory size
Permissions

Section Headers

Section index
Section type
Virtual address
File offset
Section size

The project intentionally maintains a focused scope rather than attempting to reproduce every capability of professional ELF-analysis tools.

🔮 Future Extensions

The architecture can be extended to support additional ELF information, including:

Endianness
Machine architecture
ELF file type
ELF version information
Section names and flags
Alignment information
ELF interpreter
Symbol tables
Dynamic symbols
Relocation entries
Section-to-segment mappings
Stronger malformed-input validation
Additional ELF classes and architectures
More detailed command-line options

These are considered future extensions rather than part of the current implementation.

🎓 Learning Outcomes

Building ELF Inspector provides practical experience with:

C systems programming
Binary file parsing
ELF data structures
File I/O
Fixed-width integer types
Virtual addresses and file offsets
Program loading concepts
Segment permissions and flags
Section organization
Command-line arguments
GCC compiler warnings
GNU Make
Linux executable formats

More importantly, the project demonstrates how low-level binary metadata can be transformed into information that is meaningful to a developer or systems programmer.

🔐 Security Note

ELF Inspector is designed as an inspection and learning utility.

Its core workflow reads and parses ELF metadata without executing the target ELF file:
```text
ELF File
   ↓
Read Metadata
   ↓
Parse Structures
   ↓
Display Information
```
It is not intended to replace dedicated malware-analysis, reverse-engineering, or security-analysis platforms. Untrusted binaries should still be handled in an appropriate controlled environment.

💡 Project Philosophy

Understand the binary by parsing the binary.

ELF Inspector is built around a simple idea: understanding executable files becomes much clearer when the underlying structures are inspected directly.

The project brings together:
```text
C
│
├── Binary File I/O
├── ELF Structures
├── Memory Concepts
├── Program Loading
├── Executable Formats
└── Low-level Metadata Analysis
```
Rather than treating an executable as a black box, ELF Inspector provides a practical view into the metadata that defines its structure and runtime representation.

📄 License

This project is intended primarily for educational and learning purposes
