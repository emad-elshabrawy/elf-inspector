#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

const char *get_program_type(uint32_t type)
{
    switch (type)
    {
        case PT_NULL:
            return "NULL";

        case PT_LOAD:
            return "LOAD";

        case PT_DYNAMIC:
            return "DYNAMIC";

        case PT_INTERP:
            return "INTERP";

        case PT_NOTE:
            return "NOTE";

        case PT_PHDR:
            return "PHDR";

        case PT_TLS:
            return "TLS";

        default:
            return "UNKNOWN";
    }
}

const char *get_section_type(uint32_t type)
{
    switch (type)
    {
        case SHT_NULL:
            return "NULL";

        case SHT_PROGBITS:
            return "PROGBITS";

        case SHT_SYMTAB:
            return "SYMTAB";

        case SHT_STRTAB:
            return "STRTAB";

        case SHT_RELA:
            return "RELA";

        case SHT_HASH:
            return "HASH";

        case SHT_DYNAMIC:
            return "DYNAMIC";

        case SHT_NOTE:
            return "NOTE";

        case SHT_NOBITS:
            return "NOBITS";

        case SHT_REL:
            return "REL";

        case SHT_DYNSYM:
            return "DYNSYM";

        case SHT_GNU_versym:
            return "VERSYM";

        case SHT_GNU_verneed:
            return "VERNEED";

        case SHT_GNU_HASH:
            return "GNU_HASH";

        default:
            return "UNKNOWN";
    }
}

void print_permissions(uint32_t flags)
{
    printf("%c%c%c",
           (flags & PF_R) ? 'R' : '-',
           (flags & PF_W) ? 'W' : '-',
           (flags & PF_X) ? 'X' : '-');
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <elf-file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");

    if (file == NULL)
    {
        perror("fopen");
        return 1;
    }

    Elf64_Ehdr header;

    if (fread(&header, sizeof(header), 1, file) != 1)
    {
        fprintf(stderr, "Error: could not read ELF header\n");
        fclose(file);
        return 1;
    }

    printf("ELF Inspector\n");
    printf("=============\n\n");

    printf("ELF Class    : %s\n",
           header.e_ident[EI_CLASS] == ELFCLASS64 ? "ELF64" : "Unknown");

    printf("Entry Point  : 0x%lx\n",
           (unsigned long)header.e_entry);

    printf("Program Headers : %u\n",
           header.e_phnum);

    printf("Section Headers : %u\n",
           header.e_shnum);

    printf("\nProgram Headers\n");
    printf("================\n");

    if (fseek(file, header.e_phoff, SEEK_SET) != 0)
    {
        fprintf(stderr, "Error: could not seek to program headers\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < header.e_phnum; i++)
    {
        Elf64_Phdr program_header;

        if (fread(&program_header, sizeof(program_header), 1, file) != 1)
        {
            fprintf(stderr, "Error: could not read program header\n");
            fclose(file);
            return 1;
        }

       printf("[%d] %s, Offset: 0x%lx, VirtAddr: 0x%lx, "
       "FileSize: 0x%lx, MemSize: 0x%lx, Flags: ",
       i,
       get_program_type(program_header.p_type),
       (unsigned long)program_header.p_offset,
       (unsigned long)program_header.p_vaddr,
       (unsigned long)program_header.p_filesz,
       (unsigned long)program_header.p_memsz);

      print_permissions(program_header.p_flags);

      printf("\n");
    } 
     printf("\nSection Headers\n");
     printf("================\n");

    Elf64_Shdr string_table_header;

    if (fseek(file, header.e_shoff + (header.e_shstrndx * sizeof(Elf64_Shdr)), SEEK_SET) != 0){
    fprintf(stderr, "Error: could not seek to string table header\n");
    fclose(file);
    return 1;
    }

    if (fread(&string_table_header, sizeof(string_table_header), 1, file) != 1)
    {
    fprintf(stderr, "Error: could not read string table header\n");
    fclose(file);
    return 1;
    }
    
     if (fseek(file, header.e_shoff, SEEK_SET) != 0)
     {
     perror("Failed to seek to section headers");
     fclose(file);
     return 1;
     }

     for (int i = 0; i < header.e_shnum; i++)
     {
     Elf64_Shdr section_header;

     if (fread(&section_header, sizeof(section_header), 1, file) != 1)
     {
        perror("Failed to read section header");
        fclose(file);
        return 1;
     }

     printf("[%d] %s, Address: 0x%lx, Offset: 0x%lx, "
           "Size: 0x%lx\n",
           i,
           get_section_type(section_header.sh_type),
           (unsigned long)section_header.sh_addr,
           (unsigned long)section_header.sh_offset,
           (unsigned long)section_header.sh_size);
    } 

    fclose(file);

    return 0;
}
