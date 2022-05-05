#include <proc.h>
#include <elf.h>
size_t ramdisk_read(void *buf, size_t offset, size_t len);

static uintptr_t loader(PCB *pcb, const char *filename) {
  Elf64_Ehdr elf_head;
	int a;
	a = ramdisk_read(&elf_head, 0, sizeof(Elf64_Ehdr)); 
  if (0 == a) {
		printf("fail to read head\n");
		assert(0);
	}

	// 判断elf文件类型
	if (elf_head.e_ident[0] != 0x7F ||
		elf_head.e_ident[1] != 'E' ||
		elf_head.e_ident[2] != 'L' ||
		elf_head.e_ident[3] != 'F') {
		printf("Not a ELF file\n");
		assert(0);
	}
  size_t roffset = 0;
	Elf64_Shdr *shdr = (Elf64_Shdr*)malloc(sizeof(Elf64_Shdr) * elf_head.e_shnum);
	if (NULL == shdr) {
		printf("shdr malloc failed\n");
		assert(0);
	}
  
  roffset = elf_head.e_phoff;
	a = ramdisk_read(shdr, elf_head.e_shoff, sizeof(Elf64_Shdr) * elf_head.e_shnum);
	if (0 == a) {
		printf("\nfail to read section\n");
		assert(0);
	}
  printf("loaddddd\n");
  roffset += a;
  roffset = shdr[elf_head.e_shstrndx].sh_offset;
	//fseek(elf_fp, shdr[elf_head.e_shstrndx].sh_offset, SEEK_SET);
	char shstrtab[shdr[elf_head.e_shstrndx].sh_size];
	// 读取内容
	a = ramdisk_read(shstrtab, roffset, shdr[elf_head.e_shstrndx].sh_size);
	if (0 == a) {
		printf("\nfaile to read\n");
    assert(0);
	}
  roffset = elf_head.e_phoff;
  uint8_t buf [50000];
  for (int i = 0;i < elf_head.e_phnum;++ i) {
    Elf64_Phdr tmp;
    ramdisk_read(&tmp, roffset, sizeof(Elf64_Phdr));
    if (tmp.p_type == PT_LOAD) {
      // 需要加载
      ramdisk_read(buf, tmp.p_offset, tmp.p_memsz);
      memcpy((uint8_t*)tmp.p_vaddr, buf, tmp.p_memsz);
      memset((uint8_t*)tmp.p_vaddr + tmp.p_filesz, 0, tmp.p_memsz - tmp.p_filesz);
    }
  }
  free(shdr);
  return 0;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}

