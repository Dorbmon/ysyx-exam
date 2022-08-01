#include <proc.h>
#include <elf.h>
#include <fs.h>
#include <am.h>
#include <memory.h>
size_t ramdisk_read(void *buf, size_t offset, size_t len);

static uintptr_t loader(PCB *pcb, const char *filename) {
  
  Elf64_Ehdr elf_head;
	int a;
	//a = ramdisk_read(&elf_head, 0, sizeof(Elf64_Ehdr)); 
  int fd = fs_open(filename, 0, 0);
  a = fs_read(fd, &elf_head, sizeof(Elf64_Ehdr));
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
  //roffset = elf_head.e_phoff;
  Log("enter loader");
  fs_lseek(fd, elf_head.e_phoff, SEEK_SET);
  for (int i = 0;i < elf_head.e_phnum;++ i) {
    Elf64_Phdr tmp;
    fs_read(fd, &tmp, sizeof(Elf64_Phdr));
    if (tmp.p_type == PT_LOAD) {
      int cur = fs_lseek(fd, 0, SEEK_CUR);
      fs_lseek(fd, tmp.p_offset, SEEK_SET);
      
      //memset((uint8_t*)tmp.p_vaddr + tmp.p_filesz, 0, tmp.p_memsz - tmp.p_filesz);
      for (size_t pgAll = 0;pgAll * PGSIZE < tmp.p_memsz;++ pgAll) {
        void* pg = new_page(1);
        map(&pcb->as, (void*)(tmp.p_vaddr + pgAll * PGSIZE), pg, 0);
        fs_read(fd, (uint8_t*)pg, PGSIZE);
        if (pgAll * PGSIZE > tmp.p_filesz) {
          memset(pg, 0, PGSIZE);
        }
      }
      fs_lseek(fd, cur, SEEK_SET);
    }
  }
  Log("finish load\n");
  return elf_head.e_entry;
}

void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  //Log("Jump to entry = %d\n", entry);
  ((void(*)())entry) ();
}

