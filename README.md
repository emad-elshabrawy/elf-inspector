# ELF Inspector

> A lightweight command-line ELF binary analyzer written in C for inspecting and understanding the internal structure of ELF executables and related binary files.

## 📌 Overview

**ELF Inspector** is a systems-programming and binary-analysis project that parses **ELF (Executable and Linkable Format)** files directly and presents important structural metadata in a clear, human-readable format.

Instead of relying on an existing utility such as `readelf`, the project demonstrates how ELF structures can be accessed and interpreted programmatically using C.

The main objective is not to replace professional ELF-analysis tools, but to provide a practical implementation for understanding how executable binaries are structured and how operating systems interpret their metadata.

The current implementation focuses on three fundamental ELF components:

- **ELF Header**
- **Program Headers**
- **Section Headers**

---

## 🎯 Why ELF Inspector?

Compiled executables are often treated as black boxes. ELF Inspector approaches the problem from the opposite direction: it starts from the compiled binary and exposes the information that describes its structure and runtime representation.

The project helps answer questions such as:

- What type of ELF file is this?
- Is it ELF32 or ELF64?
- Where is the program entry point?
- How many program and section headers exist?
- What segments are loaded into memory?
- Where are those segments located in the file?
- What virtual addresses do they use?
- What are their file and memory sizes?
- What permissions do they have?
- What sections exist inside the binary?
- How is the binary logically organized?

This creates a practical connection between:

```text
Source Code
     ↓
Compiler / Linker
     ↓
ELF Binary
     ↓
ELF Metadata
     ↓
Runtime Memory Representation
```
Core Features
1. ELF Header Analysis

The ELF Header is the starting point for interpreting the binary.

ELF Inspector extracts and displays important information including:

ELF class
Entry point address
Number of program headers
Number of section headers

Example:

ELF Class       : ELF64
Entry Point     : 0x10e0
Program Headers : 14
Section Headers : 31

These values provide a quick structural overview of the inspected binary.

2. Program Header Analysis

Program Headers describe segments that are relevant to loading and executing an ELF file.

The inspector displays:

Segment index
Segment type
File offset
Virtual address
File size
Memory size
Segment permissions

Example:

[2] LOAD, Offset: 0x0, VirtAddr: 0x0,
    FileSize: 0x858, MemSize: 0x858, Flags: R--

[3] LOAD, Offset: 0x1000, VirtAddr: 0x1000,
    FileSize: 0x8a5, MemSize: 0x8a5, Flags: R-X

[5] LOAD, Offset: 0x2dd0, VirtAddr: 0x3dd0,
    FileSize: 0x290, MemSize: 0x2a0, Flags: RW-

Recognized segment types are converted from numeric ELF constants into readable names such as:

PHDR, INTERP, LOAD, DYNAMIC, NOTE, GNU_STACK, and GNU_RELRO.

Unknown values are explicitly reported as UNKNOWN rather than being silently ignored.

3. Section Header Analysis

Section Headers describe the logical organization of an ELF file and are particularly relevant to compilation, linking, and binary organization.

The inspector displays:

Section index
Section type
Virtual address
File offset
Section size

Example:

[11] PROGBITS, Address: 0x1000, Offset: 0x1000, Size: 0x17
[14] PROGBITS, Address: 0x10e0, Offset: 0x10e0, Size: 0x7bb
[22] DYNAMIC, Address: 0x3de0, Offset: 0x2de0, Size: 0x1e0
[28] SYMTAB, Address: 0x0, Offset: 0x3080, Size: 0x498

The current implementation focuses on section metadata rather than dumping the complete raw contents of every section.

🧠 Program Headers vs Section Headers

One of the main concepts demonstrated by the project is the distinction between Program Headers and Section Headers.

Program Headers	Section Headers
Describe segments	Describe sections
Runtime / loading perspective	Logical / organizational perspective
Important to the loader	Important for linking and organization
Describe memory mapping	Describe file organization

A simple way to remember the difference:

Program Headers  →  How is it loaded?

Section Headers  →  How is it organized?

Understanding this distinction is fundamental when studying ELF internals.

⚙️ How It Works

ELF Inspector follows a direct parsing workflow:
```text
             ELF Binary
                  │
                  ▼
          Read ELF Metadata
                  │
                  ▼
             ELF Header
                  │
          ┌───────┴───────┐
          ▼               ▼
 Program Headers    Section Headers
          │               │
          ▼               ▼
 Segment Metadata   Section Metadata
          │               │
          └───────┬───────┘
                  ▼
        Human-readable Output
```
The project works directly with the binary representation instead of invoking readelf internally.

This keeps the implementation close to the actual ELF format and makes the parsing process easier to study.

🛠️ Technologies & Concepts
Technologies
C
GNU/Linux
ELF system structures
Make
GCC
Concepts
Binary File Parsing
ELF Internals
Operating Systems
Systems Programming
Executable File Formats
Memory Mapping
Virtual Addresses
File Offsets
Program Loading
Linking and Compilation
Reverse Engineering Fundamentals
🚀 Quick Start
Clone the Repository
git clone <repository-url>
cd elf-inspector
Build
make
Run
./elf-inspector elf-inspector

You can also inspect another ELF executable:

./elf-inspector /bin/ls
Clean Build Files
make clean
🧪 Validation

To verify the parser's output, ELF Inspector can be compared against the standard Linux readelf utility.

ELF Header
readelf -h elf-inspector
Program Headers
readelf -l elf-inspector
Section Headers
readelf -S elf-inspector

The same binary can then be analyzed using:

./elf-inspector elf-inspector

The outputs can be compared across values such as:

ELF class
Entry point
Header counts
Segment types
File offsets
Virtual addresses
File sizes
Memory sizes
Permissions
Section types
Section addresses
Section sizes

This validation approach helps ensure that the information parsed by the project corresponds to the ELF metadata reported by an established inspection utility.

🏗️ Design Decisions
Direct ELF Parsing

The project reads ELF metadata directly from the binary instead of executing readelf internally.

This is important because the goal is to understand how ELF structures are represented and accessed programmatically.

Human-readable Output

ELF structures contain many numeric constants. The project translates recognized values into meaningful names such as:

LOAD
PHDR
INTERP
DYNAMIC
NOTE
PROGBITS
SYMTAB
DYNSYM

This makes the output easier to understand and analyze.

Explicit Unknown-Type Handling

When the inspector encounters an unsupported or unknown ELF type, it reports:

UNKNOWN

instead of silently ignoring the value.

This makes the tool's behavior more transparent and helps identify areas that could be extended in future versions.

📚 Current Scope

The current version focuses specifically on ELF metadata inspection.

Supported
ELF Header
ELF Class
Entry Point
Program Header Count
Section Header Count
Program Header Metadata
Segment Types
File Offsets
Virtual Addresses
File Sizes
Memory Sizes
Segment Permissions
Section Header Metadata
Section Types
Unknown-Type Reporting
Not Intended To

ELF Inspector is not intended to be a complete replacement for readelf or professional reverse-engineering platforms.

The project intentionally maintains a focused scope around the fundamental structures required to understand ELF binaries.

🔐 Security & Safety

ELF Inspector is an inspection-only analysis utility.

The core workflow does not execute the target ELF file:
```text
ELF File
   ↓
Read Metadata
   ↓
Parse Structures
   ↓
Display Information
```
It is therefore suitable as a learning and research tool for exploring executable structures. Nevertheless, unknown or untrusted binaries should always be handled in an appropriate controlled environment.

🎓 Learning Outcomes

Through this project, the implementation demonstrates practical understanding of:

How ELF binaries are structured
How binary data can be parsed in C
How ELF headers provide the information required to interpret the file
How Program Headers describe runtime-oriented segments
How Section Headers describe logical file organization
The difference between file offsets and virtual addresses
The difference between file size and memory size
How segment permissions are represented
How low-level numeric metadata can be converted into meaningful information
How binary-parser implementations can be validated against established tools
🔮 Future Improvements

Possible extensions include:

Symbol table inspection
String table extraction
Dynamic section analysis
Relocation information
More ELF architectures and variants
Additional ELF and GNU-specific structures
More detailed error handling and malformed-file validation
Extended command-line options
Automated comparison tests against readelf
💡 Project Philosophy

Understand the binary by parsing the binary.

The main value of ELF Inspector is not simply displaying ELF information. It is understanding how that information is stored, located, interpreted, and related to the execution of a program.

The project connects:
```text
C Programming
      +
Binary File Parsing
      +
Operating Systems
      +
Executable Formats
      +
Memory Concepts
      +
Linux Internals
```
ELF Inspector is therefore a compact but practical systems-programming project that turns the ELF specification into a working binary-analysis utility.

📄 License

This project is primarily intended for educational and learning purposes.
