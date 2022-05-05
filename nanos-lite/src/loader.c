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
  roffset = elf_head.e_phoff;
  uint8_t buf [1000];
  for (int i = 0;i < elf_head.e_phnum;++ i) {
    Elf64_Phdr tmp;
    roffset += ramdisk_read(&tmp, roffset, sizeof(Elf64_Phdr));
    if (tmp.p_type == PT_LOAD) {
      // 需要加载
      printf("vaddr: %x\n", tmp.p_vaddr);
      ramdisk_read(buf, tmp.p_offset, tmp.p_filesz);
      memcpy((uint8_t*)tmp.p_vaddr, buf, tmp.p_filesz);
      memset((uint8_t*)tmp.p_vaddr + tmp.p_filesz, 0, tmp.p_memsz - tmp.p_filesz);
    }
  }
  return elf_head.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  //Log("Jump to entry = %d\n", entry);
  ((void(*)())entry) ();
}

